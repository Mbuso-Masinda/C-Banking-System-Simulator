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
    long long balance;
    int64_t balanceCache;
    std::vector<std::string> transactions;
    //void updateBalance();

public:
    Account(std::string accountNumber,
            const int64_t balanceCache)
        : accountNumber(std::move(accountNumber)),
          balance(0),
          balanceCache(balanceCache) {}

    Account(){}

    void updateBalanceCache();
    [[nodiscard]] int64_t getBalance() const { return balance; }
    [[nodiscard]] const std::string& getAccountNumber() const { return accountNumber; }
    [[nodiscard]] const int64_t& getBalanceCache() const { return balanceCache; }
    [[nodiscard]] const std::vector<std::string>& getTransactions() const { return transactions; }
    void addTransaction(const std::string& transaction) { transactions.push_back(transaction); }

    void deposit(const Transaction& transaction);
    void withdraw(const Transaction& transaction);
    void saveAccount(std::ofstream& out, const std::string& path) const;
    void loadTransactions(std::ifstream& in);
};


#endif //BANKAPP3_ACCOUNT_H