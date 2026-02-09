#include<iostream>
using namespace std;

class test{
public:
    int a;

    test( ){
        a = 8;
    }

    int nonconstFucntion( ){
        cout<<"Non Constant Function is called "<<endl;
        //a=a+10;
        return a;
    }

    int constFucntion(int a) const{
        this->a = a + 10; //error
        return a;
    }
};

int main( ){
    const test t;
    cout<<"Constant Function is called"<<endl;
    t.a = 10; // error, can't modify const objects
    cout<<t.nonconstFucntion()://error, can't call non const objects
    cout<<t.constFucntion(10);
    return 0;
}
