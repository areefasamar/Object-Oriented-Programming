#include <iostream>
using namespace std;

template <typename T1, typename T2>
T1 Max(T1 a, T2 b) {
        return a < b ? b : a;
}

template <class T1, class T2>
void someFunc(T1 var1, T2 var2) { 
}

int main() {
        cout << "Max integer are: " << Max(22, 2.77) << endl;
        cout << "Max float are: " << Max(3.9, 22) << endl;

        return 0;
}

