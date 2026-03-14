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

    bool transfer(const Transaction& transaction);
    void deposit(const Transaction& transaction);
    void withdraw(const Transaction& transaction);

    void saveBank();
    void loadBank();

    static User loadUser(const std::string& path, const std::string& name);

    static Account loadAccount(const std::string& path);
    void updateBalance();

    void openUser(const int& index);
    void login();
    void signUp();

    friend std::string createUserID(const Bank &b);
    friend std::string createTransactionID(const Bank &b);
    void openAccounts(const int& index);
    void openAccount(Account& acc, const int& index);
    bool createAccount(const int& index);
    Transaction createTransaction(const long long& amount, const int& index, const Account& acc) const;
    Transaction createTransaction(const long long& amount, const int& index, const Account& acc, const std::string& receiver);

};


#endif //BANKAPP3_BANK_H