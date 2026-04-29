#include <iostream>
using namespace std;

int Max(int a, int b) {
        return a < b ? b : a;
}

double Max(double a, double b) {
        return a < b ? b : a;
}

int main() {
        cout << Max(10, 20) << endl;
        cout << Max(1.0, 1.5) << endl;

        return 0;
}

