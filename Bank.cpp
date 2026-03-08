//
// Created by mbuso-masinda on 3/8/26.
//

#include "Bank.h"

#include <utility>

void Bank::transfer(Account& from, Account& to, Transaction& transaction) const {
    from.withdraw(transaction);
    for (auto& user : users) {
        for (auto& account : user.getAccounts()) {
            if (account.getAccountNumber() == to.getAccountNumber()) {
                to.deposit(transaction);
            }
        }
    }
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
