//
// Created by mbuso-masinda on 3/8/26.
//

#include "Transaction.h"
#include <iostream>

void Transaction::displayTransaction() const {
    std::cout << "Transaction ID: " << transactionId << std::endl
              << "User ID: " << userId << std::endl
              << "From: " << fromAccount << std::endl
              << "To: " << toAccount << std::endl
              << "Title: " << title << std::endl
              << "Amount: " << std::fixed << std::setprecision(2) << amount << std::endl;
}
