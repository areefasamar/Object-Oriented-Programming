#include <iostream>
#include <cstring> // Required for strlen and strcpy
#include <string>

using namespace std;

class Student {
private:
    // 1. Stack Member (Normal data member)
    int rollNumber;      // Allocated on the stack directly inside the object

    // 2. Heap Members (Pointers to dynamic memory)
    int* age;            
    string* status;      
    char* name;          

public:
    // Parameterized Constructor
    Student(int roll, int a, string stat, const char* n) {
        // Initializing stack member directly
        rollNumber = roll;

        // Allocating heap memory dynamically
        age = new int;
        status = new string;
        name = new char[strlen(n) + 1];

        // Storing values into heap spaces
        *age = a;
        *status = stat;
        strcpy(name, n);

        cout << "[Constructor] Object created. Roll Number allocated on Stack." << endl;
    }

    // Custom COPY CONSTRUCTOR doing both Shallow and Deep copying
    Student(const Student& source) {
        // A. Handling the Stack Member:
        // Just directly copy the value. Simple assignment is enough!
        rollNumber = source.rollNumber;

        // B. Handling the Heap Members (Deep Copy):
        // Allocate brand new separate memory slots for the clone
        age = new int;
        status = new string;
        name = new char[strlen(source.name) + 1];

        // Copy values from source object into the new slots
        *age = *(source.age);
        *status = *(source.status);
        strcpy(name, source.name);

        cout << "[Copy Constructor] Deep copy done. Roll Number cloned on Stack." << endl;
    }

    // Destructor (Only frees the heap memories)
    ~Student() {
        delete age;
        delete status;
        delete[] name; 
        // Note: We DO NOT delete 'rollNumber'. The stack memory cleans itself up automatically!
        cout << "[Destructor] Heap memory cleaned up." << endl;
    }

    void changeData(int roll, int a, string stat, const char* n) {
        rollNumber = roll; // Update stack member
        *age = a;
        *status = stat;
        
        delete[] name;
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }

    void display() const {
        cout << "Roll Number (Stack Value): " << rollNumber << " (Stored inside object frame)\n";
        cout << "Name: " << name << " (Heap Address: " << (void*)name << ")\n";
        cout << "Age: " << *age << " (Heap Address: " << age << ")\n";
        cout << "Status: " << *status << " (Heap Address: " << status << ")\n";
        cout << "---------------------------------------------------" << endl;
    }
};

int main() {
    cout << "--- Creating Original Student (s1) ---" << endl;
    // Roll: 45, Age: 20
    Student s1(45, 20, "Undergraduate", "Alice");
    s1.display();

    cout << "--- Creating Clone Student (s2) ---" << endl;
    Student s2(s1); 
    s2.display();

    cout << "--- Modifying s1 ---" << endl;
    s1.changeData(99, 21, "Graduated", "Bob");
    
    cout << "s1 updated values (Roll & Heap changed):" << endl;
    s1.display();
    
    cout << "s2 values (Roll 45 and Alice should remain perfectly intact):" << endl;
    s2.display();

    return 0;
}