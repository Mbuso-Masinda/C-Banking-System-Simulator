//
// Created by mbuso-masinda on 3/8/26.
//

#ifndef BANKAPP3_BANK_H
#define BANKAPP3_BANK_H
#include <vector>

#include "../include/User.h"


class Bank {
    std::vector<User> users;

public:

    [[nodiscard]] std::vector<User>& getUsers() { return users; }

    void signUpUser(std::string fullName,
                    std::string idNumber,
                    std::string dateOfBirth,
                    std::string phoneNumber,
                    std::string email,
                    std::string username,
                    std::string password,
                    std::string userId);
    [[nodiscard]] bool transfer(const Transaction& transaction);

    void saveBank();
};


#endif //BANKAPP3_BANK_H