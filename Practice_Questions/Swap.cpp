#include <iostream>
using namespace std;

class SwapThree {
private:
    int a, b, c;

public:
    SwapThree(int x, int y, int z) {
        a = x;
        b = y;
        c = z;
    }

    void display() {
        cout << "a = " << a
             << ", b = " << b
             << ", c = " << c << endl;
    }

    void swapUsingPointers() {
        int* p1 = &a;
        int* p2 = &b;
        int* p3 = &c;

        int temp;

        temp = *p1;
        *p1 = *p2;
        *p2 = *p3;
        *p3 = temp;
    }
};

int main() {
    SwapThree obj(10, 20, 30);

    cout << "Before swap:\n";
    obj.display();

    obj.swapUsingPointers();

    cout << "\nAfter swap:\n";
    obj.display();

    return 0;
}