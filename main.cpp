#include <iostream>
#include "include/Bank.h"

int main() {
    Account account("12345", 0), account2("54321", 0), account3("24680", 0);
    Bank bank;

    Transaction transaction2("246", "12334", "12345", "none", "deposit", 300);
    Transaction transaction3("234", "12334", "12345", "24680", "transfer", 200);

    bank.loadBank();

    //bank.signUpUser("Mbuso", "09342", "040508", "0814919232", "mbusomasinda@outlook.com", "Mlilo", "21MBMMlilo", "12334");
    //bank.signUpUser("Musa", "48334", "230206", "084625434", "musamasinda@outlook.com", "Parad3", "Password1", "234gb4");

    //bank.getUsers()[0].addAccount("12345");
    //bank.getUsers()[1].addAccount("24680");

    bank.deposit(transaction2);

    if (bank.transfer(transaction3))
        std::cout << "Transfer Successful\n" << std::endl;
    else
        std::cout << "Transfer Failed\n" << std::endl;

    bank.saveBank();
}