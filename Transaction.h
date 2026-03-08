//
// Created by mbuso-masinda on 3/8/26.
//

#ifndef BANKAPP3_TRANSACTION_H
#define BANKAPP3_TRANSACTION_H
#include <chrono>
#include <string>


class Transaction {
private:
    std::string transactionId;
    std::string userId;
    std::string fromAccount;
    std::string toAccount;
    std::string title;
    long long amount;
    std::chrono::system_clock::time_point timeStamp;

public:
    Transaction(std::string transactionId,
                std::string userId,
                std::string fromAccount,
                std::string toAccount,
                std::string title,
                const long long amount)
                    : transactionId(std::move(transactionId)),
                      userId(std::move(userId)),
                      fromAccount(std::move(fromAccount)),
                      toAccount(std::move(toAccount)),
                      amount(amount),
                      title(std::move(title)),
                      timeStamp(std::chrono::system_clock::now()){}

    virtual ~Transaction() = default;

    [[nodiscard]] const std::string& getTransactionId() const { return transactionId; }
    [[nodiscard]] const std::string& getUserId() const { return userId; }
    [[nodiscard]] const std::string& getFromAccount() const { return fromAccount; }
    [[nodiscard]] const std::string& getToAccount() const { return toAccount; }
    [[nodiscard]] const std::string& getTitle() const { return title; }
    [[nodiscard]] long long getAmount() const { return amount; }
    [[nodiscard]] std::chrono::system_clock::time_point getTimeStamp() const { return timeStamp; }

    void displayTransaction() const;

    void operator-() {
        amount *= -1;
    }
};


#endif //BANKAPP3_TRANSACTION_H