#include <iostream>
using namespace std;
class Number {
private:
    int *value;  

public:
    Number(int v) {
        value = new int(v);
        cout << "Parameterized Constructor called" << endl;
    }

    Number(const Number &obj) {
        value = new int(*(obj.value)); 
        cout << "Copy Constructor called" << endl;
    }

    void display() {
        cout << "Value: " << *value << endl;
    }

    void setValue(int v) {
        *value = v;
    }

    ~Number() {
        delete value;
        cout << "Destructor called" << endl;
    }
};

int main() {
    Number num1(100);        
    Number num2 = num1;      
    
    cout << "Before changing num2:" << endl;
    cout << "num1: "; 
	num1.display();
    cout << "num2: "; 
	num2.display();

    num2.setValue(200);      

    cout << "\nAfter changing num2:" << endl;
    cout << "num1: "; 
	num1.display(); 
    cout << "num2: "; 
	num2.display();

    Number num3(num2);
    num3.display();
    
    return 0;
}
