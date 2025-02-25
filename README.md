# Banking System

A C++ console application that simulates a basic banking system with account management and transaction tracking.

## Description

This Banking System allows users to create accounts, manage deposits and withdrawals, transfer money between accounts, and view transaction history. The application is built using object-oriented programming principles in C++.

## Features

- Create savings and checking accounts
- Deposit and withdraw funds
- Transfer money between accounts
- View account information
- Track transaction history
- List all accounts in the system

## How to Compile and Run

### Prerequisites

- C++ compiler (GCC, MinGW, or MSVC)
- Basic knowledge of terminal/command prompt

### Compilation

To compile the program, navigate to the directory containing the source code and run:

```
g++ -o banking_system main.cpp
```

### Running the Application

After compilation, run the executable:

- On Windows:
```
banking_system.exe
```

## Usage

The program presents a menu-driven interface with the following options:

1. Create New Account
2. Display Account Information
3. Deposit Money
4. Withdraw Money
5. Transfer Money
6. Display Transaction History
7. Display All Accounts
8. Exit

Follow the on-screen prompts to perform banking operations.

## Sample Operations

- Creating an account: Choose option 1 and provide account number, name, account type, and initial deposit.
- Depositing money: Choose option 3 and specify the account number and amount.
- Transferring funds: Choose option 5 and provide source account, destination account, and amount.

## Classes

The system is built with three main classes:
- `Transaction`: Stores information about individual financial transactions
- `Account`: Manages account details and transaction history
- `Bank`: Coordinates operations between accounts


## License

This project is available for educational purposes.