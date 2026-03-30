#include <iostream>
using namespace std;

class Employee {
private:
    const int EmployeeId;
    static int totalEmployees;
    static const int MAX_EMPLOYEES = 500;

public:
    Employee(int id) : EmployeeId(id) {
        totalEmployees++;
    }

    void display() const {
        cout << "ID: " << EmployeeId << endl;
        cout << "Total Employees so far: " << totalEmployees << endl;
        cout << "Max Capacity: " << MAX_EMPLOYEES << endl;
        cout << "----------------------" << endl;
    }
};

int Employee::totalEmployees = 0;

int main() {
    Employee e1(101);
    e1.display();

    Employee e2(102);
    e2.display();

    return 0;
}

