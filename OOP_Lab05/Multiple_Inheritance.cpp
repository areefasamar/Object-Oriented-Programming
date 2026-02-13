#include <iostream>
using namespace std;

class Teacher {
public:
    void teach() { cout << "I can teach lessons." << endl; }
};

class Author {
public:
    void write() { cout << "I can write books." << endl; }
};

class Scholar : public Teacher, public Author {
public:
    void research() { cout << "I am doing research." << endl; }
};

int main() {
    Scholar myScholar;
    myScholar.teach();   
    myScholar.write();    
    myScholar.research(); 
    return 0;
}
