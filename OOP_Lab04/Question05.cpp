#include <iostream>
#include <string>
using namespace std;

class HotelMercato {
private:
    string customerName;
    int daysStayed;
    static const double dailyRent;

public:
    HotelMercato(string name, int days): customerName(name), daysStayed(days) { }

    double calculateRent() const {
        int billableDays = daysStayed;

        if (daysStayed > 7) {
            billableDays -= 1;
        }

        return billableDays * dailyRent;
    }

    void display() const {
        cout << "Customer Name: " << customerName << endl;
        cout << "Days Stayed: " << daysStayed << endl;
        cout << "Total Rent: " << calculateRent() << endl;
    }
};

const double HotelMercato::dailyRent = 1000.85;

int main() {
    HotelMercato customer1("Alice", 5);
    HotelMercato customer2("Bob", 10);

    cout << "Customer 1 Details:" << endl;
    customer1.display();
    cout << endl;

    cout << "Customer 2 Details:" << endl;
    customer2.display();
    cout << endl;

    return 0;
}
