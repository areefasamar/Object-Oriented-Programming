#include <iostream>
using namespace std;
void addMatrix(int A[3][3], int B[3][3], int sum[3][3]);
void multiplyMatrix(int A[3][3], int B[3][3], int product[3][3]);
int main() {
    int A[3][3], B[3][3], sum[3][3], product[3][3];

    cout << "Enter elements of first 3x3 matrix:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
        	cout << "Enter element ("<<i+1<<","<<j+1<<"): " <<endl;
            cin >> A[i][j];
        }
    }

    cout << "Enter elements of second 3x3 matrix:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
        	cout << "Enter element ("<<i+1<<","<<j+1<<"): " <<endl;
            cin >> B[i][j];
        }
    }

    addMatrix(A, B, sum);
    multiplyMatrix(A, B, product);

    cout << "\nSum of matrices:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << sum[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nProduct of matrices:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << product[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

void addMatrix(int A[3][3], int B[3][3], int sum[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum[i][j] = A[i][j] + B[i][j];
        }
    }
}

void multiplyMatrix(int A[3][3], int B[3][3], int product[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            product[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                product[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
