#include <iostream>
#include <map>
#include <string>
#include <limits>

using namespace std;

void displayAll(const map<string, double>& grades) {
        if (grades.empty()) {
                cout << "\nThe gradebook is currently empty." << endl;
                return;
        }
        cout << "\n--- Current Gradebook ---" << endl;
        for (auto const& [name, grade] : grades) {
                cout << "Student: " << name << " | Grade: " << grade << endl;
        }
}

void retrieveGrade(const map<string, double>& grades) {
        string name;
        cout << "Enter student name to find: ";
        cin.ignore();
        getline(cin, name);

        auto it = grades.find(name);
        if (it != grades.end()) {
                cout << "Grade for " << name << ": " << it->second << endl;
        } else {
                cout << "Error: Student '" << name << "' not found." << endl;
        }
}

void updateGrade(map<string, double>& grades) {
        string name;
        cout << "Enter student name to update: ";
        cin.ignore();
        getline(cin, name);

        if (grades.count(name)) {
                double newGrade;
                cout << "Enter new grade: ";
                cin >> newGrade;
                grades[name] = newGrade;
                cout << "Grade updated successfully." << endl;
        } else {
                cout << "Error: Student not found. Use 'Add' to create a new entry." << endl;
        }
}

void deleteStudent(map<string, double>& grades) {
        string name;
        cout << "Enter student name to delete: ";
        cin.ignore();
        getline(cin, name);

        if (grades.erase(name)) {
                cout << "Student '" << name << "' removed from records." << endl;
        } else {
                cout << "Error: Student not found." << endl;
        }
}

int main() {
        map<string, double> gradebook;
        int choice;

        cout << "Welcome, Teacher! Student Grade Management System" << endl;

        while (true) {
                cout << "\n1. Add Student\n2. Retrieve Grade\n3. Update Grade\n4. Delete Student\n5. Display All\n6. Exit" << endl;
                cout << "Select an option: ";
                cin >> choice;

                if (choice == 6) break;

                switch (choice) {
                        case 1: {
                                string name;
                                double grade;
                                cout << "Enter Student Name: ";
                                cin.ignore();
                                getline(cin, name);
                                cout << "Enter Grade: ";
                                cin >> grade;
                                gradebook[name] = grade;
                                break;
                        }
                        case 2: retrieveGrade(gradebook); break;
                        case 3: updateGrade(gradebook); break;
                        case 4: deleteStudent(gradebook); break;
                        case 5: displayAll(gradebook); break;
                        default: cout << "Invalid choice. Try again." << endl;
                }
        }

        return 0;
}