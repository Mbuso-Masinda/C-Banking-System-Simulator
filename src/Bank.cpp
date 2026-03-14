//
// Created by mbuso-masinda on 3/8/26.
//

#include "../include/Bank.h"

#include <fstream>
#include <filesystem>
#include <iostream>
#include <ctime>

bool Bank::transfer(const Transaction& transaction) {
    Account *sender = nullptr;
    Account *receiver = nullptr;

    for (auto& user : users) {
        for (auto& account : user.getAccounts()) {

            if (account.getAccountNumber() == transaction.getFromAccount())
                sender = &account;

            if (account.getAccountNumber() == transaction.getToAccount())
                receiver = &account;
        }
    }

    if (!sender || !receiver)
        return false;

    receiver->addTransaction(transaction.getTransactionId());
    sender->addTransaction(transaction.getTransactionId());

    transactionLedger.emplace_back(transaction);

    return true;
}

void Bank::deposit(const Transaction &transaction) {
    Account *receiver = nullptr;

    for (auto& user : users) {
        for (auto& account : user.getAccounts()) {

            if (account.getAccountNumber() == transaction.getToAccount())
                receiver = &account;
        }
    }

    receiver->addTransaction(transaction.getTransactionId());

    transactionLedger.emplace_back(transaction);
}

void Bank::withdraw(const Transaction& transaction) {
    Account *sender = nullptr;

    for (auto& user : users) {
        for (auto& account : user.getAccounts()) {

            if (account.getAccountNumber() == transaction.getFromAccount())
                sender = &account;
        }
    }

    sender->addTransaction(transaction.getTransactionId());

    transactionLedger.emplace_back(transaction);
}

void Bank::saveBank() {
    namespace fs = std::filesystem;

    if (!fs::exists("../data/transaction_ledger"))
        fs::create_directory("../data/transaction_ledger");

    for (const auto& user : users) {
        const std::string& username = user.getUsername();
        if (!fs::exists("../data/Users/" + username))
            fs::create_directories("../data/Users/" + username);

        std::ofstream out(("../data/Users/" + username + "/") + username + "_Details.txt");

        user.saveUser(out);

        out.close();
    }

    for (auto& user : users) {
        const std::string& username = user.getUsername();

        for (auto& account : user.getAccounts()) {
            if (!fs::exists("../data/Users/" + username + "/Accounts/" + account.getAccountNumber()))
                fs::create_directories("../data/Users/" + username + "/Accounts/" + account.getAccountNumber());

            const std::string path = "../data/Users/" + username + "/Accounts/" + account.getAccountNumber();

            std::ofstream out(("../data/Users/" + username + "/Accounts/" + account.getAccountNumber() + "/accountDetails.txt"));

            account.saveAccount(out, path);

            out.close();
        }
    }

    for (const auto& transaction : transactionLedger) {

        std::ofstream ledger("../data/transaction_ledger/transactionLedger.csv");

        ledger << transaction.getTransactionId() << '|'
            << transaction.getUserId() << '|'
            << transaction.getFromAccount() << '|'
            << transaction.getToAccount() << '|'
            << transaction.getTitle() << '|'
            << transaction.getAmount() << '|'
            << std::chrono::system_clock::to_time_t(transaction.getTimeStamp())<< std::endl;

        ledger.close();
    }
}

void Bank::loadBank() {
    namespace fs = std::filesystem;

    if (fs::exists("../data/transaction_ledger")) {
        std::ifstream file("../data/transaction_ledger/transactionLedger.csv");

        if (!file.is_open()) {
            std::cerr << "Error opening tLedger\n";
            return;
        }

        std::string line;

        while (getline(file, line, '\n')) {
            Transaction t = Transaction::fromCSV(line);

            transactionLedger.push_back(t);
        }

        for (const auto& entry : fs::directory_iterator("../data/Users")) {

            std::string username = entry.path().filename();
            std::string userPath = entry.path();

            User user = loadUser(userPath, username);

            for (const auto& accEntry : fs::directory_iterator(userPath + "/Accounts"))
            {
                if (accEntry.is_directory())
                {
                    std::string accountPath = accEntry.path();

                    Account acc = loadAccount(accountPath);

                    std::ifstream in2(accountPath + "/transactionIDs.txt");

                    if (!in2.is_open()) {
                        std::cerr << "Error opening transaction ID\n";
                    }

                    while (getline(in2, line, '\n')) {
                        acc.addTransaction(line);
                    }

                    user.addAccount(acc);
                }
            }

            users.push_back(user);
        }

    }else if (fs::exists("../data/Users")) {
        for (const auto& entry : fs::directory_iterator("../data/Users")) {

            std::string username = entry.path().filename();
            std::string userPath = entry.path();

            User user = loadUser(userPath, username);

            for (const auto& accEntry : fs::directory_iterator(userPath + "/Accounts"))
            {
                if (accEntry.is_directory())
                {
                    std::string accountPath = accEntry.path();

                    Account acc = loadAccount(accountPath);

                    std::ifstream in2(accountPath + "/transactionIDs.txt");

                    if (!in2.is_open()) {
                        std::cerr << "Error opening transaction ID\n";
                    }

                    std::string line;

                    while (getline(in2, line, '\n')) {
                        acc.addTransaction(line);
                    }

                    user.addAccount(acc);
                }
            }

            users.push_back(user);
        }
    }

}

User Bank::loadUser(const std::string& path, const std::string& name) {
    std::ifstream in(path + "/" + name + "_Details.txt");

    if (!in.is_open()) {
        std::cout << "Error opening userDetails\n";
        return User();
    }

    std::string fullName, idNumber, dateOfBirth, phoneNumber, email, username, password, userId;

    getline(in, fullName);
    getline(in, idNumber);
    getline(in, dateOfBirth);
    getline(in, phoneNumber);
    getline(in, email);
    getline(in, username);
    getline(in, password);
    getline(in, userId);

    in.close();

    return User(fullName, idNumber, dateOfBirth, phoneNumber, email, username, password, userId);
}

Account Bank::loadAccount(const std::string& path) {

    std::ifstream in(path + "/accountDetails.txt");

    if (!in.is_open()) {
        std::cout << "Error opening account details: " << path << std::endl;
        return Account();
    }

    std::string accNum, balance;

    getline(in, accNum);
    getline(in, balance);

    int64_t balanceCache = std::stoll(balance);

    in.close();

    return Account(accNum, balanceCache);
}

void Bank::updateBalance(Account& acc) {
    for (auto& user : users) {
        for (auto& account : user.getAccounts()) {
            account.resetBalance();
            for (auto& transaction : account.getTransactions()) {
                for (auto& globalTransaction : transactionLedger) {
                    if (transaction == globalTransaction.getTransactionId()) {
                        if (globalTransaction.getFromAccount() == account.getAccountNumber()) {
                            std::cout << "\nWithdraw amount: " << globalTransaction.getAmount() << std::endl;
                            std::cout << account.getAccountNumber() << " : " << account.getBalance() << std::endl;
                            account.withdraw(globalTransaction.getAmount());
                        }
                        else {
                            std::cout << "\nDeposit amount: " << globalTransaction.getAmount() << std::endl;
                            std::cout << account.getAccountNumber() << " : " << account.getBalance() << std::endl;
                            account.deposit(globalTransaction.getAmount());
                        }
                    }
                }
            }
        }
    }
}

void Bank::login() {
    std::cout << "\nLogin\n\n";

    int index = 0;
    bool found = false;

    std::cout << "Enter Username: ";
    std::string username;
    std::cin >> username;

    for (size_t i =0; i < users.size(); i++) {
        if (username == users[i].getUsername()) {
            index = i;
            found = true;
            break;
        }
    }

    int j = 1;

    while (!found && j < 3) {
        std::cout << "Enter Username(user not found): ";
        std::cin >> username;

        for (size_t i =0; i < users.size(); i++) {
            if (username == users[i].getUsername()) {
                index = i;
                found = true;
                break;
            }
        }

        j++;
    }

    if (!found)
        return;


    std::cout << "Enter Password: ";
    std::string password;
    std::cin >> password;

    j = 1;

    while (!users[index].validatePassword(password) && j < 3) {
        std::cout << "Enter Password(invalid password): ";
        std::cin >> password;

        j++;
    }

    if (!users[index].validatePassword(password))
        return;

    openUser(index);
}

void Bank::signUp() {
    std::cout << "\nSignUp\n\n";

    std::cout << "Enter Full Name: ";
    std::string name;
    getline(std::cin, name, '\n');

    std::cout << "Enter ID number: ";
    std::string id;
    getline(std::cin, id, '\n');

    std::cout << "Enter date of birth(DD/MM/YYYY): ";
    std::string date;
    getline(std::cin, date, '\n');

    std::cout << "Enter phone number: ";
    std::string phone;
    getline(std::cin, phone, '\n');

    std::cout << "Enter email: ";
    std::string email;
    getline(std::cin, email, '\n');

    std::cout << "Enter username: ";
    std::string username;
    getline(std::cin, username, '\n');

    std::cout << "Enter password: ";
    std::string password;
    getline(std::cin, password, '\n');

    const std::string userID = createUserID(*this);

    User user(name, id, date, phone, email, username, password, userID);

    users.push_back(user);

    std::cout << "\nYour information:\n";

    user.displayUser();

}

void Bank::openUser(const int &index) {
    User user = users[index];
    int input = 0;
    std::cout << "\nWelcome " << user.getUsername() << std::endl << std::endl;

    std::cout << "1. Open Account\n"
              << "2. Create Account\n"
              << "3. Delete Account\n"
              << "0. Exit\n";

    std::cin >> input;

    while (input < 0 || input > 2) {
        std::cout << "Please enter a valid input\n";
        std::cout << "input: ";
        std::cin >> input;
    }

    switch (input) {
        case 1:
            openAccounts(index);
            break;
        case 2:
            if (createAccount(index))
                std::cout << "SUCCESS\n";
            else
                std::cout << "FAILED\n";
            break;
        case 3:
            break;
        case 0:
            break;
        default:
            std::cerr << "Invalid input\n";
    }
}

std::string createUserID(const Bank &b) {
    std::string userID;
    bool found = false;

    srand(time(nullptr));

    for (size_t i = 0; i < 3; i++) {
        const int j = (rand() % 26);
        const char c = j + 'A';
        userID += c;
    }

    int num = 10000 + (rand() % 99999);

    userID += std::to_string(num);

    for (size_t i = 0; i < b.users.size(); i++) {
        if (b.users[i].getUserId() == userID) {
            found = true;
            break;
        }
    }

    while (found) {
        userID.clear();
        found = false;
        for (size_t i = 0; i < 3; i++) {
            srand(time(nullptr));
            const int j = (rand() % 26);
            const char c = j + 'A';
            userID += c;
        }

        num = 10000 + (rand() % 99999);

        userID += std::to_string(num);

        for (size_t i = 0; i < b.users.size(); i++) {
            if (b.users[i].getUserId() == userID) {
                found = true;
                break;
            }
        }

        for (size_t i = 0; i < b.users.size(); i++) {
            if (b.users[i].getUserId() == userID) {
                found = true;
                break;
            }
        }
    }

    return userID;
}

void Bank::openAccounts(const int &index) {
    int input = 0;

    do {
        std::cout << "Accounts:\n\n";

        for (size_t i = 0; i < users[index].getAccounts().size(); i++) {
            std::cout << i + 1 << ". " << users[index].getAccounts()[i].getAccountNumber() << std::endl;
        }

        std::cout << "0. Exit\n";

        std::cout << "input: ";
        std::cin >> input;

        while (input < 0 || input > users[index].getAccounts().size()) {
            std::cout << "Please enter a valid input\n";
            std::cout << "input: ";
            std::cin >> input;
        }



        if (input != 0)
            openAccount(users[index].getAccounts()[input - 1], index);
    }while (input != 0);
}

void Bank::openAccount(Account& acc, const int& index) {
    std::cout << "Account number: " << acc.getAccountNumber() << std::endl << std::endl;

    int input = 0;
    long long amount = 0;

    Transaction t;
    std::string receiver;

    do {

        std::cout << "1. Deposit\n"
                  << "2. Withdraw\n"
                  << "3. Transfer\n"
                  << "0. Exit\n";

        std::cout << "input: ";
        std::cin >> input;

        while (input < 0 || input > 3) {
            std::cout << "input(Please enter a valid input): ";
            std::cin >> input;
        }

        switch (input) {
            case 1:
                std::cout << "Deposit\n\n";

                std::cout << "Enter amount: R";
                std::cin >> amount;

                t = createTransaction(amount, index, acc);
                this->deposit(t);
                break;

            case 2:
                std::cout << "Withdraw\n\n";

                std::cout << "Enter amount: R";
                std::cin >> amount;

                t = createTransaction(amount, index, acc);
                withdraw(t);
                break;
            case 3:
                std::cout << "Transfer\n\n";

                std::cout << "Enter amount: R";
                std::cin >> amount;

                std::cout << "Enter receiver account number: ";
                std::cin >> receiver;

                t = createTransaction(amount, index, acc, receiver);

                transfer(t);
                break;

            case 0:
                break;
            default:
                std::cout << "Please enter a valid input\n";
                break;

        }

    }while (input != 0);
}

Transaction Bank::createTransaction(const long long& amount, const int& index,  const Account& acc) const {
    const std::string userID = users[index].getUserId();
    const std::string fromAcc = "BANK";
    const std::string toAcc = acc.getAccountNumber();
    const std::string title = "DEPOSIT";
    const std::string transactionID = createTransactionID(*this);

    Transaction t(transactionID, userID, fromAcc, toAcc, title, amount);

    return t;
}

Transaction Bank::createTransaction(const long long& amount, const int& index,  const Account& acc, const std::string& receiver) {
    bool found = false;

    std::string toAcc;

    for (size_t i = 0; i < users[index].getAccounts().size(); i++) {
        if (users[index].getAccounts()[i].getAccountNumber() == receiver) {
            toAcc = receiver;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cerr << "Account not found\n";
        Transaction t;
        return t;
    }

    const std::string userID = users[index].getUserId();
    const std::string fromAcc = acc.getAccountNumber();

    const std::string title = "DEPOSIT";
    const std::string transactionID = createTransactionID(*this);

    Transaction t(transactionID, userID, fromAcc, toAcc, title, amount);

    return t;
}

std::string createTransactionID(const Bank &b) {
    std::string transactionID;
    bool found = false;

    srand(time(nullptr));


    long int num = 10000000 + rand() % 99999999;
    transactionID += std::to_string(num);

    num = 1000 + rand() % 9999;
    transactionID += std::to_string(num);

    return transactionID;
}

bool Bank::createAccount(const int &index) {
    bool found = false;
    std::string accountNumber;

    srand(time(nullptr));

    int num = 10000 + rand() % 99999;

    accountNumber += std::to_string(num) + " - ";

    num = 1000 + rand() % 9999;

    accountNumber += std::to_string(num) + " - ";

    num = 10 + rand() % 99;

    accountNumber += std::to_string(num);

    for (auto& user : users) {
        for (const auto& account : user.getAccounts()) {
            if (account.getAccountNumber() == accountNumber) {
                found = true;
                break;
            }
        }
    }
    while (found) {
        accountNumber = "";

        num = 10000 + rand() % 99999;

        accountNumber += std::to_string(num) + " - ";

        num = 1000 + rand() % 9999;

        accountNumber += std::to_string(num) + " - ";

        num = 10 + rand() % 99;

        accountNumber += std::to_string(num);

        for (auto& user : users) {
            for (const auto& account : user.getAccounts()) {
                if (account.getAccountNumber() == accountNumber) {
                    found = true;
                    break;
                }
            }
        }
    }

    const Account acc(accountNumber);

    users[index].addAccount(acc);

    for (int i = 0; i < users[index].getAccounts().size(); i++) {
        if (users[index].getAccounts()[i].getAccountNumber() == acc.getAccountNumber()) {
            return true;
        }
    }

    return false;
}
