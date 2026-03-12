//
// Created by mbuso-masinda on 3/8/26.
//

#include "../include/Account.h"
#include <fstream>


void Account::deposit(const long long& amount) {
    balance += amount;
}

void Account::withdraw(const long long& amount){
    balance -= amount;
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



