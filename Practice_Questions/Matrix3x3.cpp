#include <iostream>
using namespace std;

class Matrix3x3 {
private:
    int mat[3][3];

public:
    // Default Constructor
    Matrix3x3() {
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                mat[i][j] = 0;
    }

    // Constructor: Pass by 2D Array
    // Note: The second and third dimensions must be specified in parameters
    Matrix3x3(int inputArr[3][3]) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                mat[i][j] = inputArr[i][j];
            }
        }
    }

    // Operator Overloading for +
    Matrix3x3 operator+(const Matrix3x3& other) {
        Matrix3x3 result;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                result.mat[i][j] = this->mat[i][j] + other.mat[i][j];
            }
        }
        return result;
    }

    // Operator Overloading for *
    Matrix3x3 operator*(const Matrix3x3& other) {
        Matrix3x3 result;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                result.mat[i][j] = 0; 
                for(int k = 0; k < 3; k++) {
                    result.mat[i][j] += this->mat[i][k] * other.mat[k][j];
                }
            }
        }
        return result;
    }

    void display() const {
        for(int i = 0; i < 3; i++) {
            cout << "[ ";
            for(int j = 0; j < 3; j++) {
                cout << mat[i][j] << " ";
            }
            cout << "]" << endl;
        }
        cout << endl;
    }
};

int main() {
    // 1. Prepare arrays to pass to the constructor
    int arr1[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int arr2[3][3] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    // 2. Initialize objects using the "Pass by Array" method
    Matrix3x3 m1(arr1);
    Matrix3x3 m2(arr2);

    // 3. Using Overloaded Operators
    cout << "Matrix 1:" << endl;
    m1.display();

    cout << "Matrix 2:" << endl;
    m2.display();

    Matrix3x3 sum = m1 + m2; // Calls operator+
    cout << "Sum (m1 + m2):" << endl;
    sum.display();

    Matrix3x3 product = m1 * m2; // Calls operator*
    cout << "Product (m1 * m2):" << endl;
    product.display();

    return 0;
}