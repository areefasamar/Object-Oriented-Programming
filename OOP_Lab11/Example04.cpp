#include <iostream>
#include <stdexcept>
using namespace std;

void divide(int numerator, int denominator) {
        try {
                if (denominator == 0) {
                        throw runtime_error("Division by zero error");
                }

                cout << "The result is: " << float(numerator) / denominator << endl;
        }
        catch (const exception& ex) {
                cout << "Exception caught: " << ex.what() << endl;
        }
}

int main() {
        divide(10, 0);
        divide(10, 20);

        return 0;
}

