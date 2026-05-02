#include <iostream>
using namespace std;

template <typename T1, typename T2>
void swapData(T1 &a, T2 &b) {
        T1 temp = a;
        a = (T1)b;
        b = (T2)temp;
}

int main() {
        int x = 10;
        int y = 20;
        cout << "Before swap (int, int): x = " << x << ", y = " << y << endl;
        swapData(x, y);
        cout << "After swap (int, int): x = " << x << ", y = " << y << endl;

        int m = 5;
        double n = 9.5;
        cout << "\nBefore swap (int, double): m = " << m << ", n = " << n << endl;
        swapData(m, n);
        cout << "After swap (int, double): m = " << m << ", n = " << n << endl;

        char c = 'A';
        int d = 70;
        cout << "\nBefore swap (char, int): c = " << c << ", d = " << d << endl;
        swapData(c, d);
        cout << "After swap (char, int): c = " << c << ", d = " << d << endl;

        return 0;
}

