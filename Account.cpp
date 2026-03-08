//
// Created by mbuso-masinda on 3/8/26.
//

#include "Account.h"

void Account::updateBalanceCache() {
    for (const auto& transaction : transactions) {
        balance += transaction.getAmount();
    }
    balanceCache = balance;
}

void Account::deposit(Transaction& transaction) {
    transactions.emplace_back(transaction);
}

void Account::withdraw(Transaction& transaction) {
    transactions.emplace_back(transaction);
}
