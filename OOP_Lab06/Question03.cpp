#include<iostream>
#include<cmath>
using namespace std;
class Vector{
    private:
        double x;
        double y;

    public:
    	
        Vector(double xVal, double yVal) : x(xVal), y(yVal) {}

        Vector operator + (const Vector& obj){
            return Vector(x + obj.x, y + obj.y);
        }

        Vector operator - (const Vector& obj){
            return Vector(x - obj.x, y - obj.y);
        }

        Vector operator * (double scalar){
            return Vector(x * scalar, y * scalar);
        }

        Vector operator / (double scalar){
            if(scalar != 0)
                return Vector(x / scalar, y / scalar);
            else{
                cout << "Division by zero not allowed." << endl;
                return Vector(0, 0);
            }
        }

        double magnitude(){
            return sqrt(x*x + y*y);
        }

        void display(){
            cout << "(" << x << ", " << y << ")" << endl;
        }
};

int main(){
    Vector v1(3, 4);
    Vector v2(1, 2);

    Vector sum = v1 + v2;
    Vector diff = v1 - v2;
    Vector mul = v1 * 2;
    Vector div = v1 / 2;

    cout << "Vector 1: ";
    v1.display();

    cout << "Vector 2: ";
    v2.display();

    cout << "Addition: ";
    sum.display();

    cout << "Subtraction: ";
    diff.display();

    cout << "Scalar Multiplication: ";
    mul.display();

    cout << "Scalar Division: ";
    div.display();

    cout << "Magnitude of Vector 1: " << v1.magnitude() << endl;

    return 0;
}
