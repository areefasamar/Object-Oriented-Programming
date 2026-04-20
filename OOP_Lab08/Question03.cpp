#include <iostream>
using namespace std;

class Account {
    protected:
        double Balance;

    public:
        Account() {
                cout << "Enter initial balance: ";
                cin >> Balance;
        }
        
        Account(double b) : Balance(b) {}

        virtual void deposit(double amount) {
                Balance += amount;
                cout << "Deposited Rs. " << amount << ". New Balance: Rs. " << Balance << endl;
        }

        virtual void withdraw(double amount) {
                if (Balance >= amount) {
                        Balance -= amount;
                        cout << "Withdrew Rs. " << amount << ". New Balance: Rs. " << Balance << endl;
                } else {
                        cout << "Insufficient Balance!" << endl;
                }
        }

        double checkBalance() {
                return Balance;
        }
};

class InterestAccount : virtual public Account {
    protected:
        double Interest;

    public:
        InterestAccount() : Account() {
                cout << "Enter interest rate (e.g., 0.30 for 30%): ";
                cin >> Interest;
        }
        
        InterestAccount(double b, double i = 0.30) : Account(b), Interest(i) {}

        void deposit(double amount) {
                double bonus = amount * Interest;
                Balance += (amount + bonus);
                cout << "Deposited Rs. " << amount << " with Rs. " << bonus << " interest. New Balance: Rs. " << Balance << endl;
        }
};

class ChargingAccount : virtual public Account {
    protected:
        double fee;

        void withdraw(double amount) {
                if (Balance >= (amount + fee)) {
                        Balance -= (amount + fee);
                        cout << "Withdrew Rs. " << amount << " with Rs. " << fee << " fee. New Balance: Rs. " << Balance << endl;
                } else {
                        cout << "Insufficient Balance for withdrawal and fee!" << endl;
                }
        }

    public:
        ChargingAccount() : Account() {
                cout << "Enter withdrawal fee (e.g., 25): ";
                cin >> fee;
        }
        
        ChargingAccount(double b, double f = 25.0) : Account(b), fee(f) {}

};

class ACI : public InterestAccount, public ChargingAccount {
    public:
        ACI() : Account(), InterestAccount(), ChargingAccount() {}
        
        ACI(double b, double i = 0.30, double f = 25.0) : Account(b), InterestAccount(b, i), ChargingAccount(b, f) {}

        void deposit(double amount) {
                InterestAccount::deposit(amount);
        }

        void withdraw(double amount) {
                ChargingAccount::withdraw(amount);
        }

        void transfer(double amount, Account& acc) {
                cout << "Transferring Rs. " << amount << " to standard Account..." << endl;
                withdraw(amount);
                acc.deposit(amount);
        }

        void transfer(double amount, InterestAccount& acc) {
                cout << "Transferring Rs. " << amount << " to InterestAccount..." << endl;
                withdraw(amount);
                acc.deposit(amount);
        }

        void transfer(double amount, ChargingAccount& acc) {
                cout << "Transferring Rs. " << amount << " to ChargingAccount..." << endl;
                withdraw(amount);
                acc.deposit(amount);
        }
};

int main(void) {
        cout << "--- Initializing ACI Account ---" << endl;
        ACI myACI(1000.0, 0.30, 25.0);
        
        cout << "\n--- Initializing Standard Account ---" << endl;
        Account targetAcc(500.0);
        
        cout << "\n--- Initializing Interest Account ---" << endl;
        InterestAccount targetIntAcc(500.0, 0.30);
        
        cout << "\n--- Testing ACI Deposit (Should add 30% interest) ---" << endl;
        myACI.deposit(100.0);
        
        cout << "\n--- Testing ACI Withdraw (Should charge Rs 25 fee) ---" << endl;
        myACI.withdraw(200.0);
        
        cout << "\n--- Testing Transfer to Standard Account ---" << endl;
        myACI.transfer(100.0, targetAcc);
        
        cout << "\n--- Testing Transfer to Interest Account ---" << endl;
        myACI.transfer(100.0, targetIntAcc);
        
        cout << "\n--- Final Balances ---" << endl;
        cout << "ACI Account Balance: Rs. " << myACI.checkBalance() << endl;
        cout << "Standard Account Balance: Rs. " << targetAcc.checkBalance() << endl;
        cout << "Interest Account Balance: Rs. " << targetIntAcc.checkBalance() << endl;

        return 0;
}

