//
// Created by mbuso-masinda on 3/8/26.
//

#ifndef BANKAPP3_ACCOUNT_H
#define BANKAPP3_ACCOUNT_H
#include <vector>

#include "Transaction.h"


class Account {
private:
    std::string accountNumber;
    int64_t balance;
    std::vector<std::string> transactions;

public:
    Account(std::string accountNumber,
            const int64_t balance)
        : accountNumber(std::move(accountNumber)),
          balance(balance) {}

    Account(std::string accountNumber) : accountNumber(std::move(accountNumber)) {}

    Account(){}

    void updateBalanceCache();
    [[nodiscard]] int64_t getBalance() const { return balance; }
    [[nodiscard]] const std::string& getAccountNumber() const { return accountNumber; }
    [[nodiscard]] const std::vector<std::string>& getTransactions() const { return transactions; }
    void addTransaction(const std::string& transaction) { transactions.push_back(transaction); }
    void resetBalance() { balance = 0; }

    void deposit(const long long& amount);
    void withdraw(const long long& amount);
    void saveAccount(std::ofstream& out, const std::string& path) const;
    void loadTransactions(std::ifstream& in);
};


#endif //BANKAPP3_ACCOUNT_H