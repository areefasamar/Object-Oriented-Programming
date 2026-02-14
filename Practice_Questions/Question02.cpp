#include <iostream>
using namespace std;

class SavingsAccount {
private:
    double savingsBalance;
    static double annualInterestRate; // Shared across all instances

public:
    SavingsAccount(double balance) : savingsBalance(balance) {}

    static void modifyInterestRate(double newRate) {
        annualInterestRate = newRate; // Static function modifying static data
    }

    void calculateMonthlyInterest() {
        savingsBalance += (savingsBalance * annualInterestRate / 12);
    }

    double getBalance() const { return savingsBalance; }
};

// Static initialization outside class
double SavingsAccount::annualInterestRate = 0.03; 

int main() {
    SavingsAccount s1(1000.0);
    SavingsAccount::modifyInterestRate(0.05);
    s1.calculateMonthlyInterest();
    cout << "Savings after interest: $" << s1.getBalance() << endl;
    return 0;
}
