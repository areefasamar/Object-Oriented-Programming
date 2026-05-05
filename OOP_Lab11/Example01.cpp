#include <iostream>
using namespace std;

int main() {
        double numerator, denominator, answer;

        cout << "Enter numerator: ";
        cin >> numerator;
        cout << "Enter denominator: ";
        cin >> denominator;

        try {
                if (denominator == 0) {
                        // Throwing a double to match the denominator's type
                        throw denominator;
                }

                answer = numerator / denominator;
                cout << numerator << " / " << denominator << " = " << answer << endl;
        }
        catch (double num_exception) {
                cout << "Error: Cannot divide by " << num_exception << endl;
        }

        return 0;
}

