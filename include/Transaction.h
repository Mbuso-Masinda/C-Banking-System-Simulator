//
// Created by mbuso-masinda on 3/8/26.
//

#ifndef BANKAPP3_TRANSACTION_H
#define BANKAPP3_TRANSACTION_H
#include <chrono>
#include <string>


class Transaction {
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
                      title(std::move(title)),
                      amount(amount),
                      timeStamp(std::chrono::system_clock::now()){}

    Transaction(std::string transactionId,
            std::string userId,
            std::string fromAccount,
            std::string toAccount,
            std::string title,
            const long long amount,
            const std::chrono::system_clock::time_point timeStamp)
        : transactionId(std::move(transactionId)),
          userId(std::move(userId)),
          fromAccount(std::move(fromAccount)),
          toAccount(std::move(toAccount)),
          title(std::move(title)),
          amount(amount),
          timeStamp(timeStamp) {}

    virtual ~Transaction() = default;
    Transaction() : amount(0) {
    }

    [[nodiscard]] const std::string& getTransactionId() const { return transactionId; }
    [[nodiscard]] const std::string& getUserId() const { return userId; }
    [[nodiscard]] const std::string& getFromAccount() const { return fromAccount; }
    [[nodiscard]] const std::string& getToAccount() const { return toAccount; }
    [[nodiscard]] const std::string& getTitle() const { return title; }
    [[nodiscard]] long long getAmount() const { return amount; }
    [[nodiscard]] std::chrono::system_clock::time_point getTimeStamp() const { return timeStamp; }

    void displayTransaction() const;

    Transaction operator-() const {
        Transaction temp = *this;
        temp.amount *= -1;
        return temp;
    }

    static Transaction fromCSV(const std::string &line);
};


#endif //BANKAPP3_TRANSACTION_H