#include <iostream>
using namespace std;

class firstprogram {
private:
    int number1;

public:
    void set(int input1) {
        number1 = input1;
    }

    int get() {
        return number1;
    }
};
int main() {
    firstprogram myInstance;
    myInstance.set(10);           
    cout << myInstance.get() << endl; 
    return 0;
}
