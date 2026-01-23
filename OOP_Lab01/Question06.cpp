#include <iostream>
using namespace std;
int main() {
    char accountType;
    int accountNumber;
    float withdrawAmount;
    float balance = 200000;   
    float tax = 0, fee = 0;

    cout << "Enter Account Type (S for Savings, C for Current): ";
    cin >> accountType;

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    cout << "Enter Withdrawal Amount: ";
    cin >> withdrawAmount;

    if (withdrawAmount > 100000) {
        cout << "You cannot withdraw more than 100,000 at a time." << endl;
        return 0;
    }

    if (accountType == 'S' || accountType == 's') {
    
        fee = withdrawAmount * 0.02;   

        balance = balance - withdrawAmount - fee;

        if (withdrawAmount > 50000) {
            tax = balance * 0.05;    
            balance = balance - tax;
        }

        cout << "\nAccount Type: Savings";
    }
    else if (accountType == 'C' || accountType == 'c') {
        
        fee = 100;   

        balance = balance - withdrawAmount - fee;

        if (withdrawAmount > 50000) {
            tax = balance * 0.05;    
            balance = balance - tax;
        }

        cout << "\nAccount Type: Current";
    }
    else {
        cout << "Invalid account type!" << endl;
        return 0;
    }

    cout << "\nAccount Number: " << accountNumber << endl;
    cout << "Withdrawal Amount: " << withdrawAmount << endl;
    cout << "Fee Deducted: " << fee << endl;
    cout << "Tax Deducted: " << tax << endl;
    cout << "Remaining Balance: " << balance << endl;

    return 0;
}
