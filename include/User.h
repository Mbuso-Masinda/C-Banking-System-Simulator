//
// Created by mbuso-masinda on 3/8/26.
//

#ifndef BANKAPP3_USER_H
#define BANKAPP3_USER_H
#include <string>
#include <utility>
#include <vector>

#include "Account.h"


class User {
private:
    std::string fullName;
    std::string idNumber;
    std::string dateOfBirth;
    std::string phoneNumber;
    std::string email;
    std::string username;
    std::string password;
    std::string userId;
    std::vector<Account> accounts;
public:
    User(std::string fullName,
         std::string idNumber,
         std::string dateOfBirth,
         std::string phoneNumber,
         std::string email,
         std::string username,
         std::string password,
         std::string userId)
        : fullName(std::move(fullName)),
          idNumber(std::move(idNumber)),
          dateOfBirth(std::move(dateOfBirth)),
          phoneNumber(std::move(phoneNumber)),
          email(std::move(email)),
          username(std::move(username)),
          password(std::move(password)),
          userId(std::move(userId)){}

    User(){}

    void displayUser() const;

    [[nodiscard]] std::vector<Account>& getAccounts() { return accounts; }
    [[nodiscard]] const std::string& getUsername() const { return username; };
    void addAccount(const Account& account);

    void saveUser(std::ofstream& out) const;
};


#endif //BANKAPP3_USER_H