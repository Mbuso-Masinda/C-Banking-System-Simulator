//
// Created by mbuso-masinda on 3/8/26.
//

#include "../include/User.h"

#include <iostream>
#include <fstream>

void User::displayUser() const {
    std::cout << "Full Name: " << fullName << std::endl
              << "ID number: " << idNumber << std::endl
              << "Date of Birth: " << dateOfBirth << std::endl
              << "Phone Number: " << phoneNumber << std::endl
              << "Email: " << email << std::endl
              << "Username: " << username << std::endl
              << "Password: " << password << std::endl;
    std::cout << "\nAccounts:\n";

    for (const auto& account : accounts) {
        std::cout << "Account number: " << account.getAccountNumber() << std::endl
                  << "Account balance: " << account.getBalance() << std::endl << std::endl;
    }

}

void User::addAccount(std::string accountNum) {
    const Account account(std::move(accountNum), 0);
    accounts.push_back(account);
}

void User::saveUser(std::ofstream &out) const {

    out << "Full Name: " << fullName << std::endl
        << "ID number: " << idNumber << std::endl
        << "Date of Birth: " << dateOfBirth << std::endl
        << "Phone Number: " << phoneNumber << std::endl
        << "Email: " << email << std::endl
        << "Username: " << username << std::endl
        << "Password: " << password << std::endl
        << "Number of accounts: " << accounts.size() << std::endl;

}
