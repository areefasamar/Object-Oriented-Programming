#include <iostream>

class Base {
public:
    virtual ~Base() {}
    
    // 🌟 The workaround: A pure virtual function acting as a virtual constructor
    virtual Base* clone() const = 0; 
};

class Child : public Base {
private:
    int data;
public:
    Child(int val) : data(val) {}

    // Implements the clone method to return a new copy of itself
    Base* clone() const override {
        return new Child(*this); // Calls the implicit copy constructor safely!
    }
};

int main() {
    Base* ptr1 = new Child(42);

    // We don't know ptr1 is a Child, but we can still duplicate it perfectly!
    Base* ptr2 = ptr1->clone(); 

    delete ptr1;
    delete ptr2;
    return 0;
}
