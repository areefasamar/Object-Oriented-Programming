#include<iostream>
using namespace std;

class Complex{
    private:
        float real;
        float imag;

    public:
        // Constructor to initialize real and imag to 0
        Complex() : real(0), imag(0) {}

        void input(){
            cout << "Enter real and imaginary parts respectively: ";
            cin >> real;
            cin >> imag;
        }

        // Overload + operator
        Complex operator + (const Complex& obj){
            Complex temp;
            temp.real = real + obj.real;
            temp.imag = imag + obj.imag;
            return temp;
        }

        void display(){
            cout << real << " + " << imag << "i" << endl;
        }
};

int main(){
    Complex c1, c2, result;

    cout << "Enter the first complex number:" << endl;
    c1.input();

    cout << "Enter the second complex number:" << endl;
    c2.input();

    result = c1 + c2;

    cout << "Sum of the two complex numbers: ";
    result.display();

    return 0;
}