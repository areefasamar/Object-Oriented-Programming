#include<iostream>
using namespace std;

class test{
public:
    int a;

    test( ){
        a = 8;
    }

    int nonconstFucntion( ) const{
        cout<<"Non Constant Function is called "<<endl;
        // a = a + 10;   // error: cannot modify data member in const function
        return a;
    }

    int constFucntion(int a) const{
        // this->a = a + 10; // error: const function cannot modify object
        return a + 10;
    }
};

int main( ){
    const test t;

    cout<<"Constant Function is called"<<endl;

    // t.a = 10; // error: cannot modify data member of const object

    // cout << t.nonconstFucntion(); // error (before fix): non-const function call on const object
    cout << t.nonconstFucntion() << endl;

    cout << t.constFucntion(10);

    return 0;
}
