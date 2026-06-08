#include <iostream>

using namespace std; // ?? Brings cout, cin, ostream, and istream into global scope

class Vector2D {
private:
    double x;
    double y;

public:
    Vector2D(double x_val = 0, double y_val = 0) : x(x_val), y(y_val) {}

    // Declared friends inside the class (std:: removed)
    friend ostream& operator<<(ostream& out, const Vector2D& v);
    friend istream& operator>>(istream& in, Vector2D& v);
};

// ==========================================
//          GLOBAL DEFINITIONS
// ==========================================

// OUTPUT OVERLOAD (cout << v)
ostream& operator<<(ostream& out, const Vector2D& v) {
    out << "(" << v.x << ", " << v.y << ")";
    return out; 
}

// INPUT OVERLOAD (cin >> v)
istream& operator>>(istream& in, Vector2D& v) {
    cout << "Enter X component: ";
    in >> v.x;
    cout << "Enter Y component: ";
    in >> v.y;
    
    return in; 
}

int main() {
    Vector2D vec;

    // Direct input using our overloaded operator
    cin >> vec;

    // Direct output using our overloaded operator
    cout << "You entered the vector: " << vec << "\n";

    return 0;
}
