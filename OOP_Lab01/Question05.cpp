#include <iostream>
using namespace std;
float surfaceArea(float r);
float volume(float r);
int main() {
    float radius;

    cout << "Enter radius of the sphere: ";
    cin >> radius;

    cout << "Surface Area of Sphere: " << surfaceArea(radius) << endl;
    cout << "Volume of Sphere: " << volume(radius) << endl;

    return 0;
}

float surfaceArea(float r) {
    return 4 * 3.14 * r * r;
}

float volume(float r) {
    return (4.0 / 3.0) * 3.14 * r * r * r;
}
