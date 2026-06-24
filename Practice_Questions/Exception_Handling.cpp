#include <iostream>
#include <stdexcept> // Essential for using runtime_error
using namespace std;

class calculator {
public:
    double safeDivide(double a, double b) {
        if (b == 0.0) {
            throw runtime_error("divide by zero");
        }
        return a / b;
    }
};

int main() {
    calculator ob;
    
    try {
        double r = ob.safeDivide(10, 0);
        cout << r;
    }
    catch (const exception& e) {
        // e.what() is used to get the "divide by zero" message
        cerr << "Error: " << e.what() << endl;
    }
    
    return 0;
}