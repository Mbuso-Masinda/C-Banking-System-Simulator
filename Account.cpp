//
// Created by mbuso-masinda on 3/8/26.
//

#include "Account.h"

void Account::updateBalance() {
    balance = 0;
    for (const auto& transaction : transactions) {
        balance += transaction.getAmount();
    }
}

void Account::updateBalanceCache() {
    balanceCache = balance;
}

void Account::deposit(Transaction& transaction) {
    transactions.emplace_back(transaction);
    updateBalance();
}

void Account::withdraw(Transaction& transaction) {
    transactions.emplace_back(transaction);
    updateBalance();
}
