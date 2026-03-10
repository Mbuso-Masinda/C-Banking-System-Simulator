cmake_minimum_required(VERSION 4.1)
project(BankApp3)

set(CMAKE_CXX_STANDARD 20)

add_executable(BankApp3 main.cpp
        src/Transaction.cpp
        include/Transaction.h
        src/Account.cpp
        include/Account.h
        src/User.cpp
        include/User.h
        src/Bank.cpp
        include/Bank.h)
