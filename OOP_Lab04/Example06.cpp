#include<iostream>
using namespace std;

class test{
public:
    int a;

    test( ){
        a = 8;
    }

    // Made const so it can be called by a const object
    int nonconstFucntion( ) const{
        cout<<"Non Constant Function is called "<<endl;
        return a;
    }

    // Const function cannot modify data members
    int constFucntion(int a) const{
        return a + 10;
    }
};

int main( ){
    const test t;

    cout<<"Constant Function is called"<<endl;
    cout << t.nonconstFucntion() << endl;
    cout << t.constFucntion(10);

    return 0;
}

/*
EXPLANATION:

1) A const member function cannot modify any data member of the class.
   The statement "this->a = a + 10" caused an error and was removed.

2) A const object cannot modify its data members.
   The statement "t.a = 10" was removed.

3) A const object can call only const member functions.
   nonconstFucntion() was marked as const to fix this issue.

4) A syntax error was caused by using ':' instead of ';' after a function call.
   It was corrected.

RESULT:
The program now follows proper const correctness rules and compiles successfully.
*/
