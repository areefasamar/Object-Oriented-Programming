#include <iostream>
using namespace std;

class Vehicle {
public:
    void fuel() { cout << "Vehicles need fuel." << endl; }
};

class Car : public Vehicle {
public:
    void wheels() { cout << "Cars have 4 wheels." << endl; }
};

class SportsCar : public Car {
public:
    void speed() { cout << "Sports cars go fast!" << endl; }
};

int main() {
    SportsCar myCar;
    myCar.fuel();   
    myCar.wheels(); 
    myCar.speed();  
    return 0;
}
