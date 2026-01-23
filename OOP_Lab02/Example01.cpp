#include <iostream>
#include <string>
using namespace std;

class Circle {
        private:
            double radius;
            string color;

        public:
            Circle(double r, string c) {
                radius = r;
                color = c;
            }

            double getRadius() {
                return radius;
            }

            double getArea() {
                return 3.14159 * radius * radius;
            }

            string getColor() {
                return color;
            }

    
            void setRadius(double r) {
                radius = r;
            }

            void setColor(string c) {
                color = c;
            }
};

int main() {
   
    Circle c1(1.2, "blue");
    Circle c2(3.4, "green");
    cout << "Area of c1: " << c1.getArea() << endl;
    cout << "Area of c2: " << c2.getArea() << endl;
    c1.setRadius(5.5);
    c2.setRadius(6.6);
    cout << "Updated area of c1: " << c1.getArea() << endl;
    cout << "Updated area of c2: " << c2.getArea() << endl;
    c1.setColor("red");
    c2.setColor("yellow");
    cout << "Color of c1: " << c1.getColor() << endl;
    cout << "Color of c2: " << c2.getColor() << endl;
    return 0;
}
