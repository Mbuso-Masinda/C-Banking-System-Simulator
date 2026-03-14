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
              << "Password: " << password << std::endl
              << "User ID: " << userId << std::endl;

}

void User::addAccount(const Account& account) {
    accounts.push_back(account);
}

void User::saveUser(std::ofstream &out) const {

    out << fullName << std::endl
        << idNumber << std::endl
        << dateOfBirth << std::endl
        << phoneNumber << std::endl
        << email << std::endl
        << username << std::endl
        << password << std::endl
        << userId << std::endl;

}

bool User::validatePassword(const std::string &input) const {
    if (input == password)
        return true;

    return false;
}
