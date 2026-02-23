#include<iostream>
using namespace std;

class BaseClass{
    public:
        virtual void Display(){
            cout << "\nThis is Display() method of BaseClass";
        }

        void Show(){
            cout << "\nThis is Show() method of BaseClass";
        }
};

class DerivedClass : public BaseClass{
    public:
        // Overriding method
        void Display(){
            cout << "\nThis is Display() method of DerivedClass";
        }
};

int main(){
    DerivedClass dr;
    BaseClass &bs = dr;

    bs.Display();   // Calls Derived version (Runtime Polymorphism)
    dr.Show();      // Calls Base version (Not virtual)

    return 0;
}