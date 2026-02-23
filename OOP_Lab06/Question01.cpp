#include<iostream>
using namespace std;
class Shape{
	protected:
		int NoOfSides;
		double area;
	
	public:
		
		Shape(int s):NoOfSides(s), area(0) {}
		
		int getNoOfSides(){
			return NoOfSides;
		}
		
		double getarea(){
			return area;
		}
		
		void setNoOfSides(int s){
			NoOfSides = s;
		}
		
		void setarea(double a){
			area = a;
		}
};

class Rectangle : public Shape{
	protected:
        double length;
        double width;

    public:
        Rectangle(double l, double w) : Shape(4), length(l), width(w) {}

        void generateArea(){
            area = length * width;
        }
};

class Circle : public Shape{
    private:
        double radius;

    public:
        Circle(double r) : Shape(1), radius(r) {}

        void generateArea(){
            area = 3.1416 * radius * radius;
        }
};

class Triangle : public Shape{
    private:
        double height;
        double base;

    public:
        Triangle(double h, double b) : Shape(3), height(h), base(b) {}

        void generateArea(){
            area = (height * base) / 2;
        }
};
class Square : public Rectangle{
    public:
        Square(double side) : Rectangle(side, side) {}

        void checkSides(){
            if(length == width)
                cout << "Both sides are equal." << endl;
            else
                cout << "Sides are not equal." << endl;
        }

        void generateArea(){
            area = length * width;
        }
};

int main(){
    Rectangle r(5, 4);
    r.generateArea();
    cout << "Rectangle Area: " << r.getarea() << endl;

    Circle c(3);
    c.generateArea();
    cout << "Circle Area: " << c.getarea() << endl;

    Triangle t(6, 4);
    t.generateArea();
    cout << "Triangle Area: " << t.getarea() << endl;

    Square s(5);
    s.checkSides();
    s.generateArea();
    cout << "Square Area: " << s.getarea() << endl;

    return 0;
}
