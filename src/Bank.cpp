//
// Created by mbuso-masinda on 3/8/26.
//

#include "../include/Bank.h"

#include <utility>
#include <fstream>
#include <filesystem>

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

    receiver->addTransaction(transaction);
    sender->addTransaction(transaction);

    return true;
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

            for (const auto& transaction : account.getTransactions()) {
                transactionLedger.emplace_back(transaction);

                std::ofstream ledger("../data/transaction_ledger/transactionLedger.csv", std::ios::app);

                ledger << transaction.getTransactionId() << '|'
                    << transaction.getUserId() << '|'
                    << transaction.getFromAccount() << '|'
                    << transaction.getToAccount() << '|'
                    << transaction.getTitle() << '|'
                    << transaction.getAmount() << std::endl;

                ledger.close();
            }
        }
    }

}

