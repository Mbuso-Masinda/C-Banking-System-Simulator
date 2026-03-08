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
    std::vector<Transaction> transactions;

public:
    Account(std::string accountNumber,
            const int64_t balanceCache)
        : accountNumber(std::move(accountNumber)),
          balance(0),
          balanceCache(balanceCache) {}

    void updateBalanceCache();
    [[nodiscard]] const std::string& getAccountNumber() const { return accountNumber; }
    [[nodiscard]] const int64_t& getBalanceCache() const { return balanceCache; }
    [[nodiscard]] const std::vector<Transaction>& getTransactions() const { return transactions; }

    void deposit(Transaction& transaction);
    void withdraw(Transaction& transaction);
};


#endif //BANKAPP3_ACCOUNT_H