//
// Created by mbuso-masinda on 3/8/26.
//

#include "Bank.h"

#include <utility>

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
