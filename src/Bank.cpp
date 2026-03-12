//
// Created by mbuso-masinda on 3/8/26.
//

#include "../include/Bank.h"

#include <utility>
#include <fstream>
#include <filesystem>
#include <iostream>

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

void Bank::signUpUser(std::string fullName,
                      std::string idNumber,
                      std::string dateOfBirth,
                      std::string phoneNumber,
                      std::string email,
                      std::string username,
                      std::string password,
                      std::string userId) {
    User user(std::move(fullName),
              std::move(idNumber),
              std::move(dateOfBirth),
              std::move(phoneNumber),
              std::move(email),
              std::move(username),
              std::move(password),
              std::move(userId));

    users.emplace_back(std::move(user));
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

    namespace fs = std::filesystem;

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
