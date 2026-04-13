#include<iostream>
#include<string>
using namespace std;

class Employee;

class Payroll{
    public:
        void updateByFriend(Employee &emp, double newAmount);
};

class Employee{
    private:
        string name;
        int id;
        string designation;
        double salary;

    public:
        Employee(string n, int i, string d, double s) : name(n), id(i), designation(d), salary(s) { }

        void display(){
            cout << "ID: " << id << " | Name: " << name << " | Salary: " << salary << endl;
        }


        friend void Payroll::updateByFriend(Employee &emp, double newAmount);
};

void Payroll::updateByFriend(Employee &emp, double newAmount){
    emp.salary = newAmount; 
    cout << "Salary revised for " << emp.name << " via Friend Function." << endl;
}

int main(){
    Employee e2("Bob", 102, "Developer", 50000);
    Payroll p;

    e2.display();
    p.updateByFriend(e2, 55000);
    e2.display();

    return 0;
}

