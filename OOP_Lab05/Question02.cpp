#include <iostream>
using namespace std;

class Teacher {
private:
    string Name;
    int Age;
    string Institute;

public:
    void setName(string n) { Name = n; }
    void setAge(int a) { Age = a; }
    void setInstitute(string i) { Institute = i; }

    string getName() const { return Name; }
    int getAge() const { return Age; }
    string getInstitute() const { return Institute; }
};

class HumanitiesTeacher : public Teacher {
private:
    string Department = "Humanities";
    string CourseName;
    string Designation;

public:
    void setCourse(string c) { CourseName = c; }
    void setDesignation(string d) { Designation = d; }

    string getDepartment() const { return Department; }
    string getCourse() const { return CourseName; }
    string getDesignation() const { return Designation; }

    void display() const {
        cout << "\n--- Humanities Teacher ---\n";
        cout << "Name: " << getName() << endl;
        cout << "Age: " << getAge() << endl;
        cout << "Institute: " << getInstitute() << endl;
        cout << "Department: " << Department << endl;
        cout << "Course: " << CourseName << endl;
        cout << "Designation: " << Designation << endl;
    }
};

class ScienceTeacher : public Teacher {
private:
    string Department = "Science";
    string CourseName;
    string Designation;

public:
    void setCourse(string c) { CourseName = c; }
    void setDesignation(string d) { Designation = d; }

    string getDepartment() const { return Department; }
    string getCourse() const { return CourseName; }
    string getDesignation() const { return Designation; }

    void display() const {
        cout << "\n--- Science Teacher ---\n";
        cout << "Name: " << getName() << endl;
        cout << "Age: " << getAge() << endl;
        cout << "Institute: " << getInstitute() << endl;
        cout << "Department: " << Department << endl;
        cout << "Course: " << CourseName << endl;
        cout << "Designation: " << Designation << endl;
    }
};

class MathsTeacher : public Teacher {
private:
    string Department = "Maths";
    string CourseName;
    string Designation;

public:
    void setCourse(string c) { CourseName = c; }
    void setDesignation(string d) { Designation = d; }

    string getDepartment() const { return Department; }
    string getCourse() const { return CourseName; }
    string getDesignation() const { return Designation; }

    void display() const {
        cout << "\n--- Maths Teacher ---\n";
        cout << "Name: " << getName() << endl;
        cout << "Age: " << getAge() << endl;
        cout << "Institute: " << getInstitute() << endl;
        cout << "Department: " << Department << endl;
        cout << "Course: " << CourseName << endl;
        cout << "Designation: " << Designation << endl;
    }
};

int main() {
    HumanitiesTeacher h;
    ScienceTeacher s;
    MathsTeacher m;

    string name, institute, course, designation;
    int age;

    cout << "Enter Humanities Teacher Details\n";
    cout << "Name: "; cin >> name;
    cout << "Age: "; cin >> age;
    cout << "Institute: "; cin >> institute;
    cout << "Course: "; cin >> course;
    cout << "Designation: "; cin >> designation;

    h.setName(name);
    h.setAge(age);
    h.setInstitute(institute);
    h.setCourse(course);
    h.setDesignation(designation);

    cout << "\nEnter Science Teacher Details\n";
    cout << "Name: "; cin >> name;
    cout << "Age: "; cin >> age;
    cout << "Institute: "; cin >> institute;
    cout << "Course: "; cin >> course;
    cout << "Designation: "; cin >> designation;

    s.setName(name);
    s.setAge(age);
    s.setInstitute(institute);
    s.setCourse(course);
    s.setDesignation(designation);

    cout << "\nEnter Maths Teacher Details\n";
    cout << "Name: "; cin >> name;
    cout << "Age: "; cin >> age;
    cout << "Institute: "; cin >> institute;
    cout << "Course: "; cin >> course;
    cout << "Designation: "; cin >> designation;

    m.setName(name);
    m.setAge(age);
    m.setInstitute(institute);
    m.setCourse(course);
    m.setDesignation(designation);

    h.display();
    s.display();
    m.display();

    return 0;
}
