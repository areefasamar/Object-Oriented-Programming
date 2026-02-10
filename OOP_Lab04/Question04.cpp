#include <iostream>
using namespace std;

class Circle {
private:
    double radius;
    const double PI;   // constant data member

public:
    // Constructor using initializer list for const data member
    Circle(double r) : radius(r), PI(3.14159) { }

    // Const member function
    double getArea() const {
        return PI * radius * radius;
    }

    // Non-const member function
    void setRadius(double r) {
        radius = r;
    }

    // Const member function
    double getRadius() const {
        return radius;
    }

    // Const member function to access const data member
    double getPI() const {
        return PI;
    }
};

int main() {
    // Const variable
    const double fixedValue = 100.5;
    cout << "Const variable value: " << fixedValue << endl;

    Circle c1(5.0);
    cout << "Radius: " << c1.getRadius() << endl;
    cout << "Area: " << c1.getArea() << endl;

    c1.setRadius(10.0);
    cout << "New Radius: " << c1.getRadius() << endl;
    cout << "New Area: " << c1.getArea() << endl;

    // Const object
    const Circle c2(7.0);
    cout << "\nConst object radius: " << c2.getRadius() << endl;
    cout << "Const object area: " << c2.getArea() << endl;
    cout << "Const data member PI: " << c2.getPI() << endl;
    // c2.setRadius(5.0); // Error: cannot call non-const function on const object

    return 0;
}
