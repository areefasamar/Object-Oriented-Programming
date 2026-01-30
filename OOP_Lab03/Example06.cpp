#include <iostream>
#include <cstdlib> 
using namespace std;
class Wall {
private:
    double *length;
    double *height;

public:
    Wall() {
        length = nullptr;
        height = nullptr;
    }

    Wall(double len, double hgt) {
        length = new double;
        height = new double;
        if (length != nullptr && height != nullptr) {
            *length = len;
            *height = hgt;
        } else {
            exit(1); 
        }
    }

    Wall(const Wall &obj) {
        length = new double;
        height = new double;
        *length = *(obj.length);
        *height = *(obj.height);
    }

    void set_values(double len, double hei) {
        *length = len;
        *height = hei;
    }

    double calculateArea() const {
        return (*length) * (*height);
    }

    ~Wall() {
        delete length;
        delete height;
    }
};

int main() {
    Wall wall1(10.5, 8.6);      
    Wall wall2 = wall1;          

    cout << "Area of Wall 1: " << wall1.calculateArea() << endl;
    cout << "Area of Wall 2: " << wall2.calculateArea() << endl;

    wall2.set_values(2.3, 1.5);
    cout << "After changing values for Wall 2:" << endl;
    cout << "Area of Wall 1: " << wall1.calculateArea() << endl;
    cout << "Area of Wall 2: " << wall2.calculateArea() << endl;

    return 0;
}
