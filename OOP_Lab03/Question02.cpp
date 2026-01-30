#include <iostream>
using namespace std;
class TollBooth {
private:
    int cars_total;    
    double amount;    

public:
    TollBooth() {
        cars_total = 0;
        amount = 0.0;
    }

    void payingCar() {
        cars_total += 1;    
        amount += 0.50;     
    }

    void Display() {
        cout << "Number of Cars: " << cars_total << endl;
        cout << "Total Amount Collected: $" << amount << endl;
    }
};

int main() {
    TollBooth booth1, booth2;

    booth1.payingCar();
    booth1.payingCar();
    booth1.payingCar();

    booth2.payingCar();
    booth2.payingCar();

    cout << "Booth 1 totals:" << endl;
    booth1.Display();

    cout << "\nBooth 2 totals:" << endl;
    booth2.Display();

    return 0;
}
/*The program successfully simulates multiple tollbooths,
updates totals whenever a car passes, and displays accurate
totals for each booth. Each TollBooth instance maintains its
own car count and total collected amount.*/
