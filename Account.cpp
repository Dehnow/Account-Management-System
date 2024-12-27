#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <limits>
#include <vector>
using namespace std;

// Base abstract class
class Account {
protected:
    string name, identityNumber, email, phoneNumber, kraPin;
    double balance;

public:
    Account(string name, string id, string email, string phone, string kraPin)
        : name(name), identityNumber(id), email(email), phoneNumber(phone), kraPin(kraPin), balance(0.0) {}

    virtual ~Account() {}

    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;

    virtual void checkBalance() const {
        cout << "Current balance: " << balance << endl;
    }

    virtual void saveToFile(ofstream& outFile) const {
        outFile << name << "\n" << identityNumber << "\n" << email << "\n" << phoneNumber << "\n" << kraPin << "\n" << balance << endl;
    }
};

// Derived class 1: SavingsAccount
class SavingsAccount : public Account {
public:
    SavingsAccount(string name, string id, string email, string phone, string kraPin)
        : Account(name, id, email, phone, kraPin) {}

    void deposit(double amount) override {
        if (amount <= 0) throw invalid_argument("Deposit amount must be positive.");
        balance += amount;
        cout << "Deposited " << amount << ". New balance: " << balance << endl;
    }

    void withdraw(double amount) override {
        if (amount <= 0) throw invalid_argument("Withdrawal amount must be positive.");
        if (amount > balance) throw runtime_error("Insufficient funds.");
        balance -= amount;
        cout << "Withdrawn " << amount << ". New balance: " << balance << endl;
    }
};

// Derived class 2: CurrentAccount
class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(string name, string id, string email, string phone, string kraPin, double overdraftLimit = 1000.0)
        : Account(name, id, email, phone, kraPin), overdraftLimit(overdraftLimit) {}

    void deposit(double amount) override {
        if (amount <= 0) throw invalid_argument("Deposit amount must be positive.");
        balance += amount;
        cout << "Deposited " << amount << ". New balance: " << balance << endl;
    }

    void withdraw(double amount) override {
        if (amount <= 0) throw invalid_argument("Withdrawal amount must be positive.");
        if (amount > balance + overdraftLimit) throw runtime_error("Withdrawal exceeds overdraft limit.");
        balance -= amount;
        cout << "Withdrawn " << amount << ". New balance: " << balance << endl;
    }
};

// Customer class
class Customer {
private:
    string customerName;
    string customerId;
    vector<Account*> accounts;

public:
    Customer(string name, string id) : customerName(name), customerId(id) {}

    void addAccount(Account* account) {
        accounts.push_back(account);
    }

    void displayAccounts() const {
        cout << "Customer: " << customerName << " (ID: " << customerId << ")\n";
        for (const auto& account : accounts) {
            account->checkBalance();
        }
    }

    ~Customer() {
        for (auto account : accounts) {
            delete account; // Free memory
        }
    }
};

// Transaction class
class Transaction {
private:
    string transactionType;
    double amount;

public:
    Transaction(string type, double amount) : transactionType(type), amount(amount) {}

    void displayTransaction() const {
        cout << "Transaction Type: " << transactionType << ", Amount: " << amount << endl;
    }
};

// Menu function
void menu(Account* account) {
    int choice;
    do {
        cout << "\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. Exit\nChoose option: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number between 1 and 4.\n";
            continue;
        }

        try {
            switch (choice) {
                case 1: {
                    double amount;
                    cout << "Enter amount to deposit: ";
                    cin >> amount;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input for amount. Try again.\n";
                        continue;
                    }

                    account->deposit(amount);
                    break;
                }
                case 2: {
                    double amount;
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input for amount. Try again.\n";
                        continue;
                    }

                    account->withdraw(amount);
                    break;
                }
                case 3:
                    account->checkBalance();
                    break;
                case 4:
                    cout << "Exiting program.\n";
                    break;
                default:
                    cout << "Invalid option, please enter a number between 1 and 4.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    } while (choice != 4);
}

// Main function
int main() {
    string name, id, email, phone, kraPin;

    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your Identity Number: ";
    cin >> id;
    cout << "Enter your email: ";
    cin >> email;
    cout << "Enter your phone number: ";
    cin >> phone;
    cout << "Enter your KRA PIN: ";
    cin >> kraPin;

    Customer customer(name, id);

    int accountType;
    cout << "Choose account type (1: Savings, 2: Current): ";
    cin >> accountType;

    while (cin.fail() || (accountType != 1 && accountType != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter 1 for Savings or 2 for Current: ";
        cin >> accountType;
    }

    Account* account = nullptr;

    if (accountType == 1) {
        account = new SavingsAccount(name, id, email, phone, kraPin);
    } else if (accountType == 2) {
        account = new CurrentAccount(name, id, email, phone, kraPin);
    }

    customer.addAccount(account);

    menu(account);

    ofstream outFile("account_data.txt");
    if (outFile) {
        account->saveToFile(outFile);
        outFile.close();
        cout << "Account details saved successfully.\n";
    } else {
        cout << "Failed to save account details.\n";
    }

    customer.displayAccounts(); // Display all accounts after transactions

    return 0;
}
