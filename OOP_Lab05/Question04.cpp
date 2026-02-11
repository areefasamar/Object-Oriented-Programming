#include <iostream>
#include <iomanip>
using namespace std;

class Item {
protected:
    string Name;
    int Quantity;

public:
    void setItem(string n, int q) {
        Name = n;
        Quantity = q;
    }

    int getQuantity() const { return Quantity; }
    string getName() const { return Name; }

    virtual double calculatePrice() const = 0;
};   


class BakedGoods : public Item {
protected:
    double discount = 0.10;
};


class Cakes : public BakedGoods {
private:
    double price = 600;

public:
    double calculatePrice() const override {
        double total = price * Quantity;
        total -= total * discount;
        return total;
    }
};


class Bread : public BakedGoods {
private:
    double price = 200;

public:
    double calculatePrice() const override {
        double total = price * Quantity;
        total -= total * discount;
        return total;
    }
};


class Drinks : public Item {
private:
    double price = 100;
    double discount = 0.05;   

public:
    double calculatePrice() const override {
        double total = price * Quantity;
        total -= total * discount;
        return total;
    }
};


int main() {
    cout << fixed << setprecision(2);

    Cakes cake;
    Bread bread;
    Drinks drink;

    int q;

    cout << "Enter quantity of cakes: ";
    cin >> q;
    cake.setItem("Cake", q);

    cout << "Enter quantity of bread: ";
    cin >> q;
    bread.setItem("Bread", q);

    cout << "Enter quantity of drinks: ";
    cin >> q;
    drink.setItem("Drinks", q);

    double totalBill = cake.calculatePrice() +
                       bread.calculatePrice() +
                       drink.calculatePrice();

    cout << "\n--- BILL ---\n";
    cout << cake.getName() << " (Quantity: " << cake.getQuantity()
         << ") : " << cake.calculatePrice() << endl;

    cout << bread.getName() << " (Quantity: " << bread.getQuantity()
         << ") : " << bread.calculatePrice() << endl;

    cout << drink.getName() << " (Quantity: " << drink.getQuantity()
         << ") : " << drink.calculatePrice() << endl;

    cout << "Total Bill: " << totalBill << endl;

    return 0;
}
