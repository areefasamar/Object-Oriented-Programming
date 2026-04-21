#include <iostream>
#include <string>
using namespace std;

class Vehicle {
    protected:
        int carId;
        string brand;
        string model;

    public:
        Vehicle(int id, string b, string m) : carId(id), brand(b), model(m) {}
        virtual bool isAvailable() = 0;
        virtual void rent() = 0;
        virtual ~Vehicle() {}
        
        void display() {
                cout << brand << " " << model << " (ID: " << carId << ")";
        }
};

class Car : public Vehicle {
    protected:
        bool available;

    public:
        Car(int id, string b, string m) : Vehicle(id, b, m), available(true) {}

        ~Car() {}

        bool isAvailable() {
                return available;
        }

        void rent() {
                available = false;
        }

        void returnVehicle() {
                available = true;
        }
};

class RentalSystem {
    public:
        void rentVehicle(Vehicle* v) {
                if (v->isAvailable()) {
                        v->rent();
                        cout << "RentalSystem: Vehicle successfully rented." << endl;
                } 
				else {
                        cout << "RentalSystem: Sorry, vehicle is currently not available." << endl;
                }
        }

        void returnVehicle(Vehicle* v) {
                Car* c = dynamic_cast<Car*>(v);
                if (c != NULL) {
                        c->returnVehicle();
                        cout << "RentalSystem: Vehicle successfully returned." << endl;
                } 
				else {
                        cout << "RentalSystem: Error returning vehicle." << endl;
                }
        }
        
};

class Customer {
    protected:
        string name;

    public:
        Customer(string n) : name(n) {}

        void rentVehicle(Vehicle* v, RentalSystem* rs) {
                cout << name << " is attempting to rent: ";
                v->display();
                cout << endl;
                rs->rentVehicle(v);
        }

        void returnVehicle(Vehicle* v, RentalSystem* rs) {
                cout << name << " is returning: ";
                v->display(); 
                cout << endl;
                rs->returnVehicle(v);
        }
};

int main(void) {
        RentalSystem sys;
        Customer cust1("Alice");
        Customer cust2("Bob");

        Vehicle* fleet[3];

        fleet[0] = new Car(101, "Toyota", "Corolla");
        fleet[1] = new Car(102, "Honda", "Civic");
        fleet[2] = new Car(103, "Ford", "Mustang");

        cout << "--- Initial Rental Process ---" << endl;
        cust1.rentVehicle(fleet[0], &sys);
        
        cout << "\n--- Trying to rent an already rented car ---" << endl;
        cust2.rentVehicle(fleet[0], &sys);

        cout << "\n--- Renting a different available car ---" << endl;
        cust2.rentVehicle(fleet[2], &sys);

        cout << "\n--- Returning the first car ---" << endl;
        cust1.returnVehicle(fleet[0], &sys);

        cout << "\n--- Renting the newly returned car ---" << endl;
        cust2.rentVehicle(fleet[0], &sys);

        for (int i = 0; i < 3; i++) {
                delete fleet[i];
        }

        return 0;
}

