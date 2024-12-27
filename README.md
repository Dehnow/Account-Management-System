
# Account Management System Project 

This project demonstrates the implementation of a simple banking system using Object-Oriented Programming (OOP) principles in C++. It models and manages customer accounts, supporting transactions like deposit, withdrawal, and balance inquiry, with robust error handling to ensure proper account management.



## Introduction

The software system showcases the practical application of key OOP concepts such as:

- **Encapsulation**
- **Inheritance**
- **Polymorphism**
- **Abstraction**
- **Exception Handling**

The program enables users to interact with customer accounts, handling both **Savings** and **Current** account types. With a Command-Line Interface (CLI), users can perform various banking operations while also ensuring data persistence in a text file.



## Project Overview

### **Objective**
The goal is to design a system that allows customers to manage their accounts with ease, providing functionalities such as deposits, withdrawals, checking balances, and saving account details to a file.

### **Core OOP Concepts**
- **Classes and Objects**: Defines classes for managing customer data and transactions.
- **Encapsulation**: Attributes are protected within classes and are accessed via setter/getter methods.
- **Inheritance**: The `Account` base class is extended by derived classes `SavingsAccount` and `CurrentAccount`.
- **Polymorphism**: Virtual functions enable different behaviors for deposit and withdrawal operations depending on the account type.
- **Abstraction**: Abstracting common behaviors in the base `Account` class, while specific behaviors (e.g., overdraft for current accounts) are implemented in derived classes.
- **Exception Handling**: Includes error checking for invalid user input and inadequate funds for transactions.

---

## Functional Requirements

### **Class Definitions**
- **Account** (Base Class): Contains basic customer information and common account functionalities like depositing, withdrawing, and saving data.
- **SavingsAccount**, **CurrentAccount** (Derived Classes): Implements specific behaviors for different account types.
- **Customer**: Handles the user's details and manages multiple accounts associated with them.
- **Transaction**: Models individual transactions, capturing the transaction type and amount.

### **Key Features**
- **Encapsulation**: Protects account details with private attributes, providing controlled access.
- **Inheritance**: Specialized classes extend the base `Account` class with unique functionality for each account type.
- **Polymorphism**: Facilitates method overriding to implement account-specific deposit and withdrawal behavior.
- **Error Handling**: Handles user input errors, ensuring only valid operations are performed.


## Installation and Usage

### **Prerequisites**
- A C++ compiler (e.g., GCC).
- IDE or editor like **Vim** or **Visual Studio**.

### **Steps to Compile and Run**

1. Clone the repository:
   ```bash
   git clone [repository-link]
   cd banking-system
   ```

2. Compile the code:
   ```bash
   g++ main.cpp -o banking_system
   ```

3. Run the program:
   ```bash
   ./banking_system
   ```

4. Follow the on-screen prompts to create an account and perform transactions.

### **Features Provided**:
- Deposit and withdrawal operations for Savings and Current accounts.
- Account balance inquiry.
- Account information is saved to a file called `account_data.txt` after transactions.


This README file serves as an outline for how your banking system project functions. You can further enhance it by adding more project-related details as required!
