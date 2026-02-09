#include <iostream>
using namespace std;

class Employee {
private:
    string EmployeeName;   
    const int EmployeeId;  

public:
    Employee(string name, int id) : EmployeeName(name), EmployeeId(id) { }

    void setEmployeeName(string name) {
        EmployeeName = name;
    }

    string getEmployeeName() const {
        return EmployeeName;
    }

    int getEmployeeId() const {
        return EmployeeId;
    }
};

int main() {
    Employee Employee1("Alice", 101);
    Employee Employee2("Bob", 102);
    Employee Employee3("Charlie", 103);

    cout << "Employee1: " << Employee1.getEmployeeName() << ", ID: " << Employee1.getEmployeeId() << endl;
    cout << "Employee2: " << Employee2.getEmployeeName() << ", ID: " << Employee2.getEmployeeId() << endl;
    cout << "Employee3: " << Employee3.getEmployeeName() << ", ID: " << Employee3.getEmployeeId() << endl;

    Employee1.setEmployeeName("Alicia");
    Employee2.setEmployeeName("Robert");
    
    cout << "\nAfter name change:" << endl;
    cout << "Employee1: " << Employee1.getEmployeeName() << ", ID: " << Employee1.getEmployeeId() << endl;
    cout << "Employee2: " << Employee2.getEmployeeName() << ", ID: " << Employee2.getEmployeeId() << endl;
    cout << "Employee3: " << Employee3.getEmployeeName() << ", ID: " << Employee3.getEmployeeId() << endl;

    return 0;
}
