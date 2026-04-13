#include<iostream>
#include<string>
using namespace std;

class Employee{
    private:
        string name;
        int id;
        string designation;
        double salary;

    public:
        Employee(string n, int i, string d, double s) : name(n), id(i), designation(d), salary(s) { }

        void display(){
            cout << "ID: " << id << " | Name: " << name << " | Designation: " << designation << " | Salary: " << salary << endl;
        }

        friend class Payroll;
};

class Payroll{
    public:
        void updateSalary(Employee &emp, double percentage){
            cout << "Updating salary for " << emp.name << "..." << endl;
            
            double increase = emp.salary * (percentage / 100.0);
            emp.salary += increase;
        }

        void setRevisedSalary(Employee &emp, double newSalary){
            emp.salary = newSalary;
        }
};

int main(){
    Employee emp1("John Doe", 101, "Software Engineer", 50000);
    Employee emp2("Jane Smith", 102, "Project Manager", 75000);

    Payroll admin;

    cout << "--- Current Payroll Records ---" << endl;
    emp1.display();
    emp2.display();

    cout << "\n--- Applying Salary Revisions ---" << endl;
    admin.updateSalary(emp1, 10);
    
    admin.setRevisedSalary(emp2, 82000);

    cout << "\n--- Updated Payroll Records ---" << endl;
    emp1.display();
    emp2.display();

    return 0;
}

