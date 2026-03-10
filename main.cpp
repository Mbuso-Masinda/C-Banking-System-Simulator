#include <iostream>
#include "include/Bank.h"

int main() {
    Account account("12345", 0), account2("54321", 0), account3("24680", 0);
    Bank bank;

    Transaction transaction1("246", "0405", "12345", "none", "dogs", -60),
                transaction2("246", "0405", "12345", "none", "deposit", 300),
                transaction3("246", "0405", "12345", "24680", "transfer", 200),
                transaction4("246", "0405", "12345", "none", "withdraw", -150);

    bank.signUpUser("Mbuso", "09342", "040508", "0814919232", "mbusomasinda@outlook.com", "Mlilo", "21MBMMlilo", "12334");
    bank.signUpUser("Musa", "48334", "230206", "084625434", "musamasinda@outlook.com", "Parad3", "Password1", "234gb4");

    bank.getUsers()[0].addAccount("12345");
    bank.getUsers()[1].addAccount("24680");

    std::cout << "\n\nBefore transfer\n\n";

    std::cout << "Account num: " << bank.getUsers()[0].getAccounts()[0].getAccountNumber() << std::endl
              << "Balance: " << bank.getUsers()[0].getAccounts()[0].getBalanceCache() << std::endl << std::endl;

    std::cout << "Account num: " << bank.getUsers()[1].getAccounts()[0].getAccountNumber() << std::endl
              << "Balance: " << bank.getUsers()[1].getAccounts()[0].getBalanceCache() << std::endl << std::endl;

    bank.getUsers()[0].getAccounts()[0].deposit(transaction2);

    if (bank.transfer(transaction3))
        std::cout << "Transfer Successful\n" << std::endl;
    else
        std::cout << "Transfer Failed\n" << std::endl;

    std::cout << "\n\nAfter transfer\n\n";

    std::cout << "Account num: " << bank.getUsers()[0].getAccounts()[0].getAccountNumber() << std::endl
              << "Balance: " << bank.getUsers()[0].getAccounts()[0].getBalanceCache() << std::endl << std::endl;

    std::cout << "Account num: " << bank.getUsers()[1].getAccounts()[0].getAccountNumber() << std::endl
              << "Balance: " << bank.getUsers()[1].getAccounts()[0].getBalanceCache() << std::endl << std::endl;

    std::cout << "\n\nUpdated cache\n\n";

    bank.getUsers()[0].getAccounts()[0].updateBalanceCache();
    bank.getUsers()[1].getAccounts()[0].updateBalanceCache();

    std::cout << "Account num: " << bank.getUsers()[0].getAccounts()[0].getAccountNumber() << std::endl
              << "Balance: " << bank.getUsers()[0].getAccounts()[0].getBalanceCache() << std::endl << std::endl;

    std::cout << "Account num: " << bank.getUsers()[1].getAccounts()[0].getAccountNumber() << std::endl
              << "Balance: " << bank.getUsers()[1].getAccounts()[0].getBalanceCache() << std::endl << std::endl;


}