#include <iostream>
#include <string>
using namespace std;
class Vehicle {
    protected:
        string type;
        string make;
        string model;
        string color;
        int year;
        int milesDriven;

    public:
        Vehicle(string t, string mk, string md, string c, int y, int mdriven): type(t), make(mk), model(md), color(c), year(y), milesDriven(mdriven) {}

        string getType(){ 
		    return type; 
		}
		
        string getMake(){ 
		    return make;
		}
        string getModel(){ 
		    return model;
		}
		
        string getColor(){ 
		    return color;
		}
		
        int getYear(){ 
		    return year; 
		}
        
		int getMilesDriven(){ 
		return milesDriven; 
		}
};

class GasVehicle : virtual public Vehicle {
    protected:
        int fuelTankSize;

    public:
        GasVehicle(string t, string mk, string md, string c, int y, int mdriven, int fTank)
		    : Vehicle(t, mk, md, c, y, mdriven), fuelTankSize(fTank) {}

        int getFuelTankSize(){ 
		    return fuelTankSize; 
		}
};

class ElectricVehicle : virtual public Vehicle {
    protected:
        int energyStorage;

    public:
        ElectricVehicle(string t, string mk, string md, string c, int y, int mdriven, int eStorage)
		    : Vehicle(t, mk, md, c, y, mdriven), energyStorage(eStorage) {}

        int getEnergyStorage(){ 
		    return energyStorage; 
		}
};

class HighPerformance : public GasVehicle {
    protected:
        int horsePower;
        int topSpeed;

    public:
        HighPerformance(string t, string mk, string md, string c, int y, int mdriven, int fTank, int hp, int ts)
		    : Vehicle(t, mk, md, c, y, mdriven), GasVehicle(t, mk, md, c, y, mdriven, fTank), horsePower(hp), topSpeed(ts) {}

        int getHorsePower(){ 
		    return horsePower; 
		}
        int getTopSpeed(){ 
		    return topSpeed; 
		}
};

class SportsCar : public HighPerformance {
    protected:
        string gearbox;
        string driveSystem;

    public:
        SportsCar(string t, string mk, string md, string c, int y, int mdriven, int fTank, int hp, int ts, string gb, string ds)
		: Vehicle(t, mk, md, c, y, mdriven), HighPerformance(t, mk, md, c, y, mdriven, fTank, hp, ts), gearbox(gb), driveSystem(ds) {}

        string getGearbox(){ 
		    return gearbox; 
		}
        string getDriveSystem(){ 
		    return driveSystem;
		}
};

class HeavyVehicle : public GasVehicle, public ElectricVehicle {
    protected:
        int maxWeight;
        int numWheels;
        int length;

    public:
        HeavyVehicle(string t, string mk, string md, string c, int y, int mdriven, int fTank, int eStorage, int weight, int wheels, int len)
            : Vehicle(t, mk, md, c, y, mdriven),
              GasVehicle(t, mk, md, c, y, mdriven, fTank),
              ElectricVehicle(t, mk, md, c, y, mdriven, eStorage),
              maxWeight(weight), numWheels(wheels), length(len) {}

        int getMaxWeight(){ 
		    return maxWeight; 
		}
        int getNumWheels(){ 
		    return numWheels; 
		}
        int getLength(){ 
		    return length; 
		}
};

class ConstructionTruck : public HeavyVehicle {
    protected:
        string cargo;

    public:
        ConstructionTruck(string t, string mk, string md, string c, int y, int mdriven, int fTank, int eStorage, int weight, int wheels, int len, string cg)
            : Vehicle(t, mk, md, c, y, mdriven), HeavyVehicle(t, mk, md, c, y, mdriven, fTank, eStorage, weight, wheels, len), cargo(cg) {}

        string getCargo(){ 
		    return cargo; 
		}
};

class Bus : public HeavyVehicle {
    protected:
        int numSeats;

    public:
        Bus(string t, string mk, string md, string c, int y, int mdriven, int fTank, int eStorage, int weight, int wheels, int len, int seats)
            : Vehicle(t, mk, md, c, y, mdriven), HeavyVehicle(t, mk, md, c, y, mdriven, fTank, eStorage, weight, wheels, len), numSeats(seats) {}

        int getNumSeats(){ 
		    return numSeats; 
		}

        void display() {
                cout << "==== Bus Details ====" << endl;
                cout << "Type: " << type << endl;
                cout << "Make: " << make << endl;
                cout << "Model: " << model << endl;
                cout << "Color: " << color << endl;
                cout << "Year: " << year << endl;
                cout << "Miles Driven: " << milesDriven << endl;
                cout << "Fuel Tank Size: " << fuelTankSize << endl;
                cout << "Energy Storage: " << energyStorage << endl;
                cout << "Maximum Weight: " << maxWeight << endl;
                cout << "Number of Wheels: " << numWheels << endl;
                cout << "Length: " << length << endl;
                cout << "Number of Seats: " << numSeats << endl;
                cout << "=====================" << endl;
        }
};

int main(void) {
        Bus myBus("Passenger Bus", "Higer", "9700", "White", 2022, 15000, 110, 50, 40000, 6, 45, 55);
        myBus.display();

        return 0;
}

