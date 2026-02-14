#include <iostream>
#include <string>
using namespace std;

class Account {
private:
    double accountBalance; // Encapsulated data

public:
    // Constructor with validation
    Account(double initialBalance) {
        if (initialBalance >= 0) {
            accountBalance = initialBalance;
        } else {
            accountBalance = 0;
            cout << "Error: Initial balance cannot be negative. Set to 0." << endl;
        }
    }

    void credit(double amount) {
        if (amount > 0) accountBalance += amount;
    }

    double getBalance() const { // Const because it only reads data
        return accountBalance;
    }
};
