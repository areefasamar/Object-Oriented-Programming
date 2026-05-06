#include <iostream>
using namespace std;

class MyException {
    public:
        const char * what() {
                return "Attempted to divide by zero!\n";
        }
};

int main() {
        try {
                int x, y;
                cout << "Enter the two numbers : \n";
                cin >> x >> y;

                if (y == 0) {
                        MyException z;
                        throw z;
                } else {
                        cout << "x / y = " << x / y << endl;
                }
        }
        catch (MyException& e) {
                cout << e.what();
        }

        return 0;
}

