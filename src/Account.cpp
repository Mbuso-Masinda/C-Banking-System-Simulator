//
// Created by mbuso-masinda on 3/8/26.
//

#include "../include/Account.h"
#include <fstream>

/*void Account::updateBalance() {
    balance = 0;
    for (const auto& transaction : transactions) {
        balance += transaction.getAmount();
    }
}*/

void Account::updateBalanceCache() {
    balanceCache = getBalance();
}

void Account::deposit(const Transaction& transaction) {
    transactions.emplace_back(transaction.getTransactionId());
    //updateBalance();
}

void Account::withdraw(const Transaction& transaction){
    transactions.emplace_back(transaction.getTransactionId());
    //updateBalance();
}

void Account::saveAccount(std::ofstream &out, const std::string& path) const {
    out << accountNumber << std::endl
        << balance << std::endl;

    std::ofstream outAccount(path + "/transactionIDs.txt");

    for (const auto& transaction : transactions) {
        outAccount << transaction << std::endl;
    }

    outAccount.close();
}

void Account::loadTransactions(std::ifstream& in) {
    std::string line;
    while (getline(in, line, '\n')) {
        transactions.emplace_back(line);
    }
}



