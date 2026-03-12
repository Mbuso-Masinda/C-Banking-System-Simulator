#include <iostream>
#include "include/Bank.h"

int main() {
    Bank bank;

    bank.loadBank();

    bank.updateBalance(bank.getUsers()[1].getAccounts()[0]);
    std::cout << bank.getUsers()[1].getAccounts()[0].getBalance();

    Transaction t("TR323", "12334", "BANK", "12345", "DEPOSIT", 600);

    bank.deposit(t);

    std::cout << std::endl;
    bank.updateBalance(bank.getUsers()[1].getAccounts()[0]);
    std::cout << bank.getUsers()[0].getAccounts()[0].getBalance() << std::endl;
    std::cout << bank.getUsers()[1].getAccounts()[0].getBalance();

}