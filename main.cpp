#include <iostream>
#include "Account.h"

int main() {
    Account account("12345", 100);

    Transaction transaction1("246", "0405", "12345", "none", "dogs", -60),
                transaction2("246", "0405", "12345", "none", "deposit", +200);

    std::cout << "Account num: " << account.getAccountNumber() << std::endl
              << "Balance: " << account.getBalanceCache() << std::endl;

    std::cout << "\nTransactions: \n";

    for (const auto& transaction : account.getTransactions()) {
        transaction.displayTransaction();
        std::cout << "===========\n";
    }

    std::cout << "\nWithdraw for dogs\n\n";
    account.withdraw(transaction1);

    std::cout << "Account num: " << account.getAccountNumber() << std::endl
              << "Balance: " << account.getBalanceCache() << std::endl;

    std::cout << "\nTransactions: \n";

    for (const auto& transaction : account.getTransactions()) {
        transaction.displayTransaction();
        std::cout << "===========\n";
    }

    std::cout << "\nDeposit for dogs\n\n";
    account.deposit(transaction2);

    account.updateBalanceCache();

    std::cout << "Account num: " << account.getAccountNumber() << std::endl
              << "Balance: " << account.getBalanceCache() << std::endl;

    std::cout << "\nTransactions: \n";

    for (const auto& transaction : account.getTransactions()) {
        transaction.displayTransaction();
        std::cout << "===========\n";
    }
}