#include <iostream>
#include <fstream>
using namespace std;

class Person {
public:
    char name[50];
    int age;

    // Change constructor to take const char*:
    Person(const char* n, int a) {
        strcpy(name, n);
        age = a;
    }
};

int main() {
    Person person1("Areefa", 18);

    // Write to binary file
    ofstream fout("person.bin", ios::binary);
    fout.write((char*)&person1, sizeof(person1));
    fout.close();

    // Read from binary file
    Person temp("", 0);
    ifstream fin("person.bin", ios::binary);
    fin.read((char*)&temp, sizeof(temp));
    fin.close();

    cout << "Name: " << temp.name << endl;
    cout << "Age: " << temp.age << endl;

    return 0;
}

