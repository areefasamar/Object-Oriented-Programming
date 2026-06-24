#include <iostream>
using namespace std;

class Shape {
protected:
    int numberOfSides;
    double area;

public:
    Shape(int n) {
        numberOfSides = n;
        area = 0;
    }

    // Pure virtual function
    virtual void generateArea() = 0;

    void setSides(int n) {
        numberOfSides = n;
    }

    int getSides() {
        return numberOfSides;
    }

    double getArea() {
        return area;
    }

    virtual void display() {
        cout << "Number of Sides: " << numberOfSides << endl;
        cout << "Area: " << area << endl;
    }

    virtual ~Shape() {}
};

class Rectangle : public Shape {
protected:
    double length;
    double width;

public:
    Rectangle(double l, double w)
        : Shape(4) {
        length = l;
        width = w;
    }

    void generateArea() {
        area = length * width;
    }

    void display() {
        cout << "\n--- Rectangle ---" << endl;
        cout << "Length: " << length << endl;
        cout << "Width: " << width << endl;
        cout << "Area: " << area << endl;
    }
};

class Circle : public Shape {
protected:
    double radius;

public:
    Circle(double r)
        : Shape(0) {
        radius = r;
    }

    void generateArea() {
        area = 3.1416 * radius * radius;
    }

    void display() {
        cout << "\n--- Circle ---" << endl;
        cout << "Radius: " << radius << endl;
        cout << "Area: " << area << endl;
    }
};

class Triangle : public Shape {
protected:
    double height;
    double base;

public:
    Triangle(double h, double b)
        : Shape(3) {
        height = h;
        base = b;
    }

    void generateArea() {
        area = (height * base) / 2;
    }

    void display() {
        cout << "\n--- Triangle ---" << endl;
        cout << "Height: " << height << endl;
        cout << "Base: " << base << endl;
        cout << "Area: " << area << endl;
    }
};

class Square : public Rectangle {

public:
    Square(double side)
        : Rectangle(side, side) {
    }

    void checkSides() {
        if (length == width) {
            cout << "Both sides are equal." << endl;
        }
        else {
            cout << "Sides are not equal." << endl;
        }
    }

    void generateArea() {
        area = length * width;
    }

    void display() {
        cout << "\n--- Square ---" << endl;
        cout << "Side: " << length << endl;
        cout << "Area: " << area << endl;
    }
};

int main() {

    // Base class pointers
    Shape* s1 = new Rectangle(5, 4);
    Shape* s2 = new Circle(3);
    Shape* s3 = new Triangle(6, 8);
    Shape* s4 = new Square(5);

    // Runtime polymorphism
    s1->generateArea();
    s1->display();

    s2->generateArea();
    s2->display();

    s3->generateArea();
    s3->display();

    s4->generateArea();
    s4->display();

    // Accessing Square specific function
    Square* sq = dynamic_cast<Square*>(s4);

    if (sq != NULL) {
        sq->checkSides();
    }

    delete s1;
    delete s2;
    delete s3;
    delete s4;

    return 0;
}