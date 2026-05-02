#include <iostream>
using namespace std;

template <class T1, class T2>
class Calculator {
        T1 num1;
        T2 num2;

    public:
        Calculator(T1 n1, T2 n2) {
                num1 = n1;
                num2 = n2;
        }

        auto add() {
                return num1 + num2;
        }

        auto subtract() {
                return num1 - num2;
        }

        auto multiply() {
                return num1 * num2;
        }

        auto divide() {
                if (num2 == 0) {
                        return (double)0;
                }
                return (double)num1 / num2;
        }

        void display() {
                cout << "Addition: " << add() << endl;
                cout << "Subtraction: " << subtract() << endl;
                cout << "Multiplication: " << multiply() << endl;
                cout << "Division: " << divide() << endl;
        }
};

int main() {
        cout << "--- Same Types (int, int) ---" << endl;
        Calculator<int, int> calc1(20, 10);
        calc1.display();

        cout << "\n--- Different Types (int, double) ---" << endl;
        Calculator<int, double> calc2(10, 2.5);
        calc2.display();

        cout << "\n--- Different Types (float, int) ---" << endl;
        Calculator<float, int> calc3(5.5f, 2);
        calc3.display();

        return 0;
}
