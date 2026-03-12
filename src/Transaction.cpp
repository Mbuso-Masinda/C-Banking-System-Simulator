//
// Created by mbuso-masinda on 3/8/26.
//

#include "../include/Transaction.h"
#include <iostream>


void Transaction::displayTransaction() const {
    std::cout << "Transaction ID: " << transactionId << std::endl
              << "User ID: " << userId << std::endl
              << "From: " << fromAccount << std::endl
              << "To: " << toAccount << std::endl
              << "Title: " << title << std::endl
              << "Amount: " << std::fixed << std::setprecision(2) << amount << std::endl;
}

Transaction Transaction::fromCSV(const std::string &line) {
    std::istringstream ss(line);
    std::string newTransactionId, newUserId, newFromAccount, newToAccount, newTitle, newAmount, timestampStr;

    getline(ss, newTransactionId, '|');
    getline(ss, newUserId, '|');
    getline(ss, newFromAccount, '|');
    getline(ss, newToAccount, '|');
    getline(ss, newTitle, '|');
    getline(ss, newAmount, '|');
    getline(ss, timestampStr, '|');

    long long newNewAmount = std::stof(newAmount);

    time_t rawTime = std::stoll(timestampStr);
    auto timePoint = std::chrono::system_clock::from_time_t(rawTime);

    return Transaction(newTransactionId, newUserId, newFromAccount, newToAccount, newTitle, newNewAmount, timePoint);
}
