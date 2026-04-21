#include <iostream>
using namespace std;

class Store {
    protected:
        double total_bill;
    public:
        Store(double bill) : total_bill(bill) {}
        virtual void calculateFinalBill() = 0;
        virtual ~Store() {}   
};

class ImtiazStore : public Store {
    public:
        ImtiazStore(double bill) : Store(bill) {}

        void calculateFinalBill() {
                double discount = total_bill * 0.07;
                double final_bill = total_bill - discount;
                cout << "--- Imtiaz Store ---" << endl;
                cout << "Original Bill: Rs. " << total_bill << endl;
                cout << "Discount (7%): Rs. " << discount << endl;
                cout << "Final Bill: Rs. " << final_bill << endl << endl;
        }
};

class BinHashimStore : public Store {
    public:
        BinHashimStore(double bill) : Store(bill) {}

        void calculateFinalBill() {
                double discount = total_bill * 0.05;
                double final_bill = total_bill - discount;
                cout << "--- Bin Hashim Store ---" << endl;
                cout << "Original Bill: Rs. " << total_bill << endl;
                cout << "Discount (5%): Rs. " << discount << endl;
                cout << "Final Bill: Rs. " << final_bill << endl << endl;
        }
};

int main(void) {
        double billAmount = 5000.0;

        ImtiazStore imtiaz(billAmount);
        BinHashimStore binHashim(billAmount);

        imtiaz.calculateFinalBill();
        binHashim.calculateFinalBill();

        return 0;
}

