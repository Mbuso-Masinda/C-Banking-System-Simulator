//
// Created by mbuso-masinda on 3/8/26.
//

#include "../include/Account.h"
#include <fstream>

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

void Account::saveAccount(std::ofstream &out, const std::string& path) const {
    out << "Account Number: " << accountNumber << std::endl
        << "Balance: " << balance << std::endl;

    std::ofstream outAccount(path + "/transactionIDs.txt");

    for (const auto& transaction : transactions) {
        outAccount << transaction.getTransactionId() << std::endl;
    }

    outAccount.close();
}
