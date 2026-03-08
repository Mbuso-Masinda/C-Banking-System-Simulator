cmake_minimum_required(VERSION 4.1)
project(BankApp3)

set(CMAKE_CXX_STANDARD 20)

add_executable(BankApp3 main.cpp
        Transaction.cpp
        Transaction.h
        Account.cpp
        Account.h)
