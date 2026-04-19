#include <iostream>
using namespace std;
class Base {
    protected:
        int x;

    public:
        Base(int i) { x = i; }
        virtual void fun() = 0;
};

class Derived : public Base {
        int y;

    public:
        Derived(int i, int j) : Base(i) { y = j; }
        void fun() { cout << "x = " << x << ", y = " << y; }
};

int main(void) {
        Derived d(4, 5);
        d.fun();

        return 0;
}

