#include <iostream>
using namespace std;

class Account {
private:
    int account_no;
    double account_bal;
    int security_code;
    static int object_count;

public:
    void initialize(int accNo, double bal, int code) {
        account_no = accNo;
        account_bal = bal;
        security_code = code;
        object_count++; 
    }

    void print() const {
        cout << "Account No: " << account_no << ", Balance: " << account_bal 
             << ", Security Code: " << security_code << endl;
    }

    static int getObjectCount() {
        return object_count;
    }
};

int Account::object_count = 0;

int main() {
    Account acc1, acc2, acc3;

    acc1.initialize(101, 5000.50, 1234);
    acc2.initialize(102, 10000.00, 5678);
    acc3.initialize(103, 7500.25, 9012);

    acc1.print();
    acc2.print();
    acc3.print();

    cout << "Total number of Account objects initialized: " << Account::getObjectCount() << endl;

    return 0;
}
