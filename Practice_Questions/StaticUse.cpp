#include <iostream>
using namespace std;

class Student {
private:
    string name;

    // Static data member
    static int totalStudents;

public:

    // Constructor
    Student(string n) {
        name = n;
        totalStudents++;

        cout << name << " object created." << endl;
    }

    // Normal member function
    void display() {
        cout << "Student Name: " << name << endl;
    }

    // Static member function
    static void showTotalStudents() {

        // Can access only static members directly
        cout << "Total Students: "
             << totalStudents << endl;
    }
};

// Definition of static data member
int Student::totalStudents = 0;

int main() {

    Student s1("Ali");
    Student s2("Ahmed");
    Student s3("Sara");

    cout << endl;

    s1.display();
    s2.display();
    s3.display();

    cout << endl;

    // Calling static function using class name
    Student::showTotalStudents();

    return 0;
}