#include<iostream>
using namespace std;
class Calculator{
    private:
        double Num1;
        double Num2;
        double Num3;

    public:
    
        Calculator(double n1, double n2, double n3) : Num1(n1), Num2(n2), Num3(n3) {}

        double add(double a, double b){
            return a + b;
        }

        double add(double a, double b, double c){
            return a + b + c;
        }

        double multiply(double a, double b){
            return a * b;
        }

        double multiply(double a, double b, double c){
            return a * b * c;
        }

        double subtract(){
            return Num1 - Num2;
        }

        double divide(){
            if(Num2 != 0)
                return Num1 / Num2;
            else{
                cout << "Division by zero not allowed." << endl;
                return 0;
            }
        }
};

int main(){
    double n1, n2, n3;
    cout << "Enter three numbers: ";
    cin >> n1 >> n2 >> n3;
    Calculator calc(n1, n2, n3);

    cout << "Addition (2 numbers): " << calc.add(n1, n2) << endl;
    cout << "Addition (3 numbers): " << calc.add(n1, n2, n3) << endl;

    cout << "Multiplication (2 numbers): " << calc.multiply(n1, n2) << endl;
    cout << "Multiplication (3 numbers): " << calc.multiply(n1, n2, n3) << endl;

    cout << "Subtraction (Num1 - Num2): " << calc.subtract() << endl;
    cout << "Division (Num1 / Num2): " << calc.divide() << endl;

    return 0;
}