#include <iostream>
#include "include/Bank.h"

void login(Bank& bank);

int main() {
    int input = 0;
    Bank bank;

    bank.loadBank();

    do {
        std::cout << "Welcome to the BANK SIMULATOR\n\n";

        std::cout << "1. Login\n"
                  << "2. Sign Up\n"
                  << "0. Quit\n";


        std::cout << "input: ";
        std::cin >> input;

        while (input < 0 || input > 2) {
            std::cout << "Please enter a valid input\n";
            std::cout << "input: ";
            std::cin >> input;
        }

        switch (input) {
            case 1:
                std::cin.ignore();
                bank.login();
                break;
            case 2:
                std::cin.ignore();
                bank.signUp();

                bank.saveBank();
                break;
            case 0:
                break;
            default:
                std::cerr << "Please enter a valid input\n";
        }
    }while (input != 0);


    bank.saveBank();

    return 0;
}


