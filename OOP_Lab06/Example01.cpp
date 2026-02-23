#include<iostream>
using namespace std;
class overload{
    public:

        // function with 1 int parameter
        void func(int x){
            cout << "value of x is " << x << endl;
        }

        // function with 1 double parameter
        void func(double x){
            cout << "value of x is " << x << endl;
        }

        // function with 2 int parameters
        void func(int x, int y){
            cout << "value of x and y is " << x << ", " << y << endl;
        }
};

int main(){
    overload obj1;

    // Calls func(int)
    obj1.func(7);

    // Calls func(double)
    obj1.func(9.132);

    // Calls func(int, int)
    obj1.func(85, 64);

    return 0;
}
