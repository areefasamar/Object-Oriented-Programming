#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    string firstName;
    static int count; // Track number of objects in memory

public:
    Employee(string name) : firstName(name) {
        count++; // Increment on creation
    }

    ~Employee() {
        count--; // Decrement on destruction
        cout << "Destructor called for " << firstName << endl;
    }

    string getFirstName() const { return firstName; } // Const read-only function

    static int getCount() { return count; }
};

int Employee::count = 0;

int main() {
    cout << "Initial Count: " << Employee::getCount() << endl;
    {
        Employee e1("John");
        Employee e2("Jane");
        cout << "Count inside block: " << Employee::getCount() << endl;
    } // e1 and e2 are destroyed here (reverse order of construction)
    cout << "Count after block: " << Employee::getCount() << endl;
    return 0;
}
