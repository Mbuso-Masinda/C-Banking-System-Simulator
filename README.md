# Bank System (C++)

A command-line banking system built in **C++** that simulates core banking operations such as account management, deposits, withdrawals, transfers, and transaction tracking.

This project was built to deepen understanding of **object-oriented design, system architecture, and financial transaction modeling**.

---

## Features

* User registration system
* Multiple accounts per user
* Deposit and withdrawal operations
* Secure transfer between accounts
* Transaction history tracking
* File persistence (data saved to disk)
* Clean modular architecture using OOP

---

## Architecture Overview

The system is structured using a layered design:

Bank

  └── Users

         └── Accounts

                └── Transactions
└── Global transaction handling

### Core Classes

**Bank**

* Manages users and system-wide operations
* Handles transfers between accounts
* Controls system-level persistence

**User**

* Represents a bank customer
* Owns multiple accounts

**Account**

* Stores balance and transaction history
* Supports deposit and withdrawal operations

**Transaction**

* Represents movement of money
* Stores transaction metadata such as:

    * transaction ID
    * source account
    * destination account
    * amount
    * timestamp

---

## Technologies Used

* C++20
* Object-Oriented Programming
* STL containers
* File handling
* Filesystem library
* Chrono library for timestamps

---

## Example Operations

Deposit:
BANK → Account

Withdrawal:
Account → BANK

Transfer:
Account A → Account B

---

## Learning Goals

This project focuses on learning:

* Software architecture
* Object-oriented design
* Financial system modeling
* File persistence
* Debugging complex systems
* Writing scalable C++ applications

---

## Project Status

Currently under active development.

Completed:

* Core architecture
* Account management
* Transactions
* File persistence (saving)

In progress:

* Data loading
* CLI interface
* additional banking features

---

## Future Improvements

* Full command-line interface
* Account authentication
* Fraud detection simulation
* Interest calculations
* Transaction search and filtering
* Performance improvements

---

## Author

Masinda Mbuso

---

## Purpose

This project was built as a **learning project to explore deeper programming concepts beyond syntax**, including system design and software engineering practices.
