#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// Custom Exception Class
class InsufficientFunds : public runtime_error {
private:
    double requested;
    double available;

public:
    // Constructor passes a message to runtime_error and stores the amounts
    InsufficientFunds(double req, double avail) 
        : runtime_error("Error: Insufficient funds for this transaction."), 
          requested(req), 
          available(avail) {}

    // Accessor methods to retrieve the specific values
    double getRequested() const { return requested; }
    double getAvailable() const { return available; }
};

class BankAccount {
private:
    double balance;

public:
    BankAccount(double initialBalance) : balance(initialBalance) {}

    void withdraw(double amount) {
        if (amount > balance) {
            // Throwing the custom exception with data
            throw InsufficientFunds(amount, balance);
        }
        balance -= amount;
        cout << "Successfully withdrew: $" << amount << endl;
        cout << "Remaining balance: $" << balance << endl;
    }
};

int main() {
    BankAccount myAccount(500.0); // Start with $500

    try {
        cout << "Attempting to withdraw $650.0..." << endl;
        myAccount.withdraw(650.0);
    } 
    catch (const InsufficientFunds& e) {
        // Demonstrate what() and the specific accessors
        cerr << e.what() << endl;
        cerr << "Requested: $" << e.getRequested() << endl;
        cerr << "Available: $" << e.getAvailable() << endl;
    }

    return 0;
}