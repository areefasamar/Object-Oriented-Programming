#include <iostream>
#include <fstream>
using namespace std;
class student {
    int roll;
    char name[25];
    float marks;
public:
    void getdata() {
        cout << "Enter roll no: ";
        cin >> roll;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter marks: ";
        cin >> marks;
    }

    void addRecord() {
        fstream f;
        student s;
        f.open("student.dat", ios::app | ios::binary);
        s.getdata();
        f.write((char*)&s, sizeof(s));
        f.close();
    }
};
int main() {
    student s;
    char c = 'n';
    do {
        s.addRecord();
        cout << "Do you want to add another record? Press Y to continue: ";
        cin >> c;
    } while (c == 'y' || c == 'Y');

    cout << endl << "Data written successfully";
    return 0;
}



