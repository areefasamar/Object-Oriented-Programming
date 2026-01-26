#include <iostream>
using namespace std;
class BankAccount
{
    private:
        double balance;
        int transactions;

    public:
        BankAccount()
        {
            balance = 0.0;
            transactions = 0;
        }

        void deposit(double amount)
        {
            balance = balance + amount;
            transactions++;
        }

        void withdraw(double amount)
        {
            if (amount <= balance)
            {
                balance = balance - amount;
                transactions++;
            }
            else
            {
                cout << "Insufficient balance!" << endl;
            }
        }
 
        void displayBalance()
        {
            cout << "Account Balance: $" << balance << endl;
        }

        void displayTransactions()
        {
            cout << "Number of Transactions: " << transactions << endl;
        }

        void displayInterest()
        {
            double interest;
            interest = balance * 0.03;   
            cout << "Interest Earned: $" << interest << endl;
        }
};
int main()
{
    BankAccount account;
    int choice;
    double amount;

    do
    {
        cout << "\nMenu\n";
        cout << "1. Display the account balance\n";
        cout << "2. Display the number of transactions\n";
        cout << "3. Display interest earned for this period\n";
        cout << "4. Make a deposit\n";
        cout << "5. Make a withdrawal\n";
        cout << "6. Exit the program\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            account.displayBalance();
            break;

        case 2:
            account.displayTransactions();
            break;

        case 3:
            account.displayInterest();
            break;

        case 4:
            cout << "Enter deposit amount: ";
            cin >> amount;
            account.deposit(amount);
            break;

        case 5:
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            account.withdraw(amount);
            break;

        case 6:
            cout << "Thank you for using ABC Bank!" << endl;
            break;

        default:
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 6);

    return 0;
}