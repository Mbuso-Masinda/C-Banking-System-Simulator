//
// Created by mbuso-masinda on 3/8/26.
//

#ifndef BANKAPP3_BANK_H
#define BANKAPP3_BANK_H
#include <vector>

#include "../include/User.h"


class Bank {
    std::vector<User> users;
    std::vector<Transaction> transactionLedger;

public:

    [[nodiscard]] std::vector<User>& getUsers() { return users; }

    [[nodiscard]] bool transfer(const Transaction& transaction);
    void deposit(const Transaction& transaction);
    void withdraw(const Transaction& transaction);

    void saveBank();
    void loadBank();

    static User loadUser(const std::string& path, const std::string& name);

    static Account loadAccount(const std::string& path);
    void updateBalance(Account& acc);

    void openUser(const int& index);
    void login();
    void signUp();

    friend std::string createUserID(const Bank &b);

};


#endif //BANKAPP3_BANK_H