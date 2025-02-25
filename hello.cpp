#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

using namespace std;

// Class to represent a transaction
class Transaction {
private:
    time_t timestamp;
    string type;
    double amount;
    string description;

public:
    Transaction(string t, double a, string desc = "") {
        timestamp = time(nullptr);
        type = t;
        amount = a;
        description = desc;
    }

    void display() const {
        char timeStr[26];
        ctime_s(timeStr, sizeof(timeStr), &timestamp);
        string timeString(timeStr);
        // Remove newline character from ctime output
        if (!timeString.empty() && timeString[timeString.length()-1] == '\n') {
            timeString.erase(timeString.length()-1);
        }

        cout << left << setw(25) << timeString 
             << setw(10) << type
             << setw(15) << fixed << setprecision(2) << amount
             << description << endl;
    }

    // Getters
    string getType() const { return type; }
    double getAmount() const { return amount; }
    time_t getTimestamp() const { return timestamp; }
};

// Class to represent a bank account
class Account {
private:
    int accountNumber;
    string accountHolder;
    double balance;
    string accountType;
    vector<Transaction> transactions;

public:


    // Constructor
    Account(int accNum, string holder, string type, double initialDeposit = 0.0) {
        accountNumber = accNum;
        accountHolder = holder;
        accountType = type;
        balance = initialDeposit;
        
        if (initialDeposit > 0) {
            transactions.push_back(Transaction("DEPOSIT", initialDeposit, "Initial deposit"));
        }
    }

    // Getters
    int getAccountNumber() const { return accountNumber; }
    string getAccountHolder() const { return accountHolder; }
    double getBalance() const { return balance; }
    string getAccountType() const { return accountType; }


    // Deposit money
    bool deposit(double amount, string desc = "Regular deposit") {
        if (amount <= 0) {
            cout << "Invalid amount for deposit." << endl;
            return false;
        }

        balance += amount;
        transactions.push_back(Transaction("DEPOSIT", amount, desc));
        cout << "Deposit successful. New balance: $" << fixed << setprecision(2) << balance << endl;
        return true;
    }

    // Withdraw money
    bool withdraw(double amount, string desc = "Regular withdrawal") {
        if (amount <= 0) {
            cout << "Invalid amount for withdrawal." << endl;
            return false;
        }

        if (balance < amount) {
            cout << "Insufficient funds. Current balance: $" << fixed << setprecision(2) << balance << endl;
            return false;
        }

        balance -= amount;
        transactions.push_back(Transaction("WITHDRAW", -amount, desc));
        cout << "Withdrawal successful. New balance: $" << fixed << setprecision(2) << balance << endl;
        return true;
    }

    // Display account information
    void displayInfo() const {
        cout << "\nAccount Information:" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    // Display transaction history
    void displayTransactions() const {
        cout << "\nTransaction History for Account #" << accountNumber << ":" << endl;
        cout << left << setw(25) << "Date & Time" 
             << setw(10) << "Type" 
             << setw(15) << "Amount ($)" 
             << "Description" << endl;
        cout << string(80, '-') << endl;

        if (transactions.empty()) {
            cout << "No transactions found." << endl;
            return;
        }

        for (const Transaction& t : transactions) {
            t.display();
        }
    }
};

// Class to manage the banking system
class Bank {

private:
    string bankName;
    vector<Account> accounts;

    // Find account by account number
    int findAccountIndex(int accountNumber) const {
        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccountNumber() == accountNumber) {
                return static_cast<int>(i);
            }
        }
        return -1;  // Not found
    }

public:
    // Constructor
    Bank(string name) : bankName(name) {}


    // Create a new account
    bool createAccount(int accountNumber, string holder, string type, double initialDeposit = 0.0) {
        // Check if account number already exists
        if (findAccountIndex(accountNumber) != -1) {
            cout << "Account with number " << accountNumber << " already exists." << endl;
            return false;
        }

        accounts.push_back(Account(accountNumber, holder, type, initialDeposit));
        cout << "Account created successfully." << endl;
        return true;
    }

    // Make a deposit
    bool deposit(int accountNumber, double amount) {
        int index = findAccountIndex(accountNumber);
        if (index == -1) {
            cout << "Account not found." << endl;
            return false;
        }

        return accounts[index].deposit(amount);
    }

    // Make a withdrawal
    bool withdraw(int accountNumber, double amount) {
        int index = findAccountIndex(accountNumber);
        if (index == -1) {
            cout << "Account not found." << endl;
            return false;
        }

        return accounts[index].withdraw(amount);
    }

    // Transfer money between accounts
    bool transfer(int fromAccount, int toAccount, double amount) {
        int fromIndex = findAccountIndex(fromAccount);
        int toIndex = findAccountIndex(toAccount);

        if (fromIndex == -1 || toIndex == -1) {
            cout << "One or both accounts not found." << endl;
            return false;
        }

        if (accounts[fromIndex].getBalance() < amount) {
            cout << "Insufficient funds for transfer." << endl;
            return false;
        }

        accounts[fromIndex].withdraw(amount, "Transfer to account #" + to_string(toAccount));
        accounts[toIndex].deposit(amount, "Transfer from account #" + to_string(fromAccount));
        cout << "Transfer completed successfully." << endl;
        return true;
    }

    // Display account information
    bool displayAccount(int accountNumber) {
        int index = findAccountIndex(accountNumber);
        if (index == -1) {
            cout << "Account not found." << endl;
            return false;
        }

        accounts[index].displayInfo();
        return true;
    }

    // Display transaction history
    bool displayTransactions(int accountNumber) {
        int index = findAccountIndex(accountNumber);
        if (index == -1) {
            cout << "Account not found." << endl;
            return false;
        }

        accounts[index].displayTransactions();
        return true;
    }

    // Display all accounts
    void displayAllAccounts() const {
        cout << "\n=== All Accounts at " << bankName << " ===" << endl;
        
        if (accounts.empty()) {
            cout << "No accounts found." << endl;
            return;
        }

        cout << left << setw(15) << "Account No." 
             << setw(25) << "Account Holder" 
             << setw(15) << "Account Type" 
             << "Balance ($)" << endl;
        cout << string(80, '-') << endl;

        for (const Account& acc : accounts) {
            cout << left << setw(15) << acc.getAccountNumber()
                 << setw(25) << acc.getAccountHolder()
                 << setw(15) << acc.getAccountType()
                 << fixed << setprecision(2) << acc.getBalance() << endl;
        }
    }
};

// Main function with menu-driven interface
int main() {
    Bank bank("C++ Bank");
    int choice;

    // Create some sample accounts
    bank.createAccount(1001, "John Doe", "Savings", 1000.0);
    bank.createAccount(1002, "Jane Smith", "Checking", 500.0);


    do {
        cout << "\n=== C++ Banking System ===" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Display Account Information" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Transfer Money" << endl;
        cout << "6. Display Transaction History" << endl;
        cout << "7. Display All Accounts" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice (1-8): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int accNum;
                string holder, type;
                double initialDeposit;
            
                cout << "Enter Account Number: ";
                cin >> accNum;
                
                cout << "Enter Account Holder Name: ";
                cin >> holder;
                
                cout << "Enter Account Type (Savings/Checking): ";
                cin >> type;
                
                cout << "Enter Initial Deposit Amount: $";
                cin >> initialDeposit;
            
                bank.createAccount(accNum, holder, type, initialDeposit);
                break;
            }
            case 2: {
                int accNum;
                cout << "Enter Account Number: ";
                cin >> accNum;
                bank.displayAccount(accNum);
                break;
            }
            case 3: {
                int accNum;
                double amount;
                cout << "Enter Account Number: ";
                cin >> accNum;
                cout << "Enter Deposit Amount: $";
                cin >> amount;
                bank.deposit(accNum, amount);
                break;
            }
            case 4: {
                int accNum;
                double amount;
                cout << "Enter Account Number: ";
                cin >> accNum;
                cout << "Enter Withdrawal Amount: $";
                cin >> amount;
                bank.withdraw(accNum, amount);
                break;
            }
            case 5: {
                int fromAcc, toAcc;
                double amount;
                cout << "Enter From Account Number: ";
                cin >> fromAcc;
                cout << "Enter To Account Number: ";
                cin >> toAcc;
                cout << "Enter Transfer Amount: $";
                cin >> amount;
                bank.transfer(fromAcc, toAcc, amount);
                break;
            }
            case 6: {
                int accNum;
                cout << "Enter Account Number: ";
                cin >> accNum;
                bank.displayTransactions(accNum);
                break;
            }
            case 7: {
                bank.displayAllAccounts();
                break;
            }
            case 8: {
                cout << "Thank you for using C++ Banking System. Goodbye!" << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
            }
        }

    } while (choice != 8);

    return 0;
}