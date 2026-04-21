#include <iostream>
using namespace std;

class ArrayMultiplier {
    public:
        virtual void calculate() = 0;
        virtual ~ArrayMultiplier(){}
};

class ArrayMultiplier1D : public ArrayMultiplier {
    protected:
        int* arr;
        int size;

    public:
        ArrayMultiplier1D(int* a, int s) : arr(a), size(s) {}

        void calculate() {
                long long product = 1;
                for (int i = 0; i < size; i++) {
                        product *= arr[i];
                }
                cout << "Product of 1D Array elements: " << product << endl;
        }
};

class ArrayMultiplier2D : public ArrayMultiplier {
    protected:
        int** arr;
        int rows;
        int cols;

    public:
        ArrayMultiplier2D(int** a, int r, int c) : arr(a), rows(r), cols(c) {}

        void calculate() {
                long long product = 1;
                for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) {
                                product *= arr[i][j];
                        }
                }
                cout << "Product of 2D Array elements: " << product << endl;
        }
};

int main(void) {
        int array1[] = {2, 3, 4, 5};
        ArrayMultiplier1D mult1D(array1, 4);
        
        mult1D.calculate();

        int r = 2;
        int c = 3;
        
        int** array2 = new int*[r];
        for (int i = 0; i < r; i++) {
                array2[i] = new int[c];
        }
        
        int value = 1;
        for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                        array2[i][j] = value++;
                }
        }

        ArrayMultiplier2D mult2D(array2, r, c);
        
        mult2D.calculate();

        for (int i = 0; i < r; i++) {
                delete[] array2[i];
        }
        delete[] array2;

        return 0;
}

