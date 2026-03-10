//
// Created by mbuso-masinda on 3/8/26.
//

#include "../include/Account.h"

void Account::updateBalance() {
    balance = 0;
    for (const auto& transaction : transactions) {
        balance += transaction.getAmount();
    }
}

void Account::updateBalanceCache() {
    balanceCache = getBalance();
}

void Account::deposit(const Transaction& transaction) {
    transactions.emplace_back(transaction);
    updateBalance();
}

void Account::withdraw(const Transaction& transaction){
    transactions.emplace_back(-transaction);
    updateBalance();
}
