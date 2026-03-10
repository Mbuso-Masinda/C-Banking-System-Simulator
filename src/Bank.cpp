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

    receiver->deposit(transaction);
    sender->withdraw(transaction);

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

    for (const auto& user : users) {
        const std::string username = user.getUsername();
        if (!fs::exists("../data/Users/" + username))
            fs::create_directory("../data/Users/" + username);

        if (!fs::exists("../data/Global_Transactions"))
            fs::create_directory("../data/Global_Transactions");

        std::ofstream out(("../data/Users/" + username + "/") + username + "_Details.txt");

        user.saveUser(out);
    }


}
