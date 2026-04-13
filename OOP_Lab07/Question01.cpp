#include<iostream>
#include<cstdlib>
using namespace std;

class Array2D{
    int rows, cols;
    int **ptr;

    public:
        Array2D(int r = 0, int c = 0) : rows(r), cols(c){
            if(rows > 0 && cols > 0){
                ptr = new int*[rows];
                for(int i = 0; i < rows; i++){
                    ptr[i] = new int[cols];
                }
            }
            else{
                ptr = NULL;
            }
        }

        Array2D(const Array2D& ob){
            rows = ob.rows;
            cols = ob.cols;
            if(rows > 0 && cols > 0){
                ptr = new int*[rows];
                for(int i = 0; i < rows; i++){
                    ptr[i] = new int[cols];
                    for(int j = 0; j < cols; j++){
                        ptr[i][j] = ob.ptr[i][j];
                    }
                }
            }
            else{
                ptr = NULL;
            }
        }

        Array2D& operator=(const Array2D& ob){
            if(this != &ob){
                for(int i = 0; i < rows; i++) delete[] ptr[i];
                delete[] ptr;

                rows = ob.rows;
                cols = ob.cols;
                ptr = new int*[rows];
                for(int i = 0; i < rows; i++){
                    ptr[i] = new int[cols];
                    for(int j = 0; j < cols; j++){
                        ptr[i][j] = ob.ptr[i][j];
                    }
                }
            }
            return *this;
        }

        int* operator[](int index){
            if(index >= rows || index < 0){
                cout << "Row index " << index << " out of bounds" << endl;
                exit(1);
            }
            return ptr[index];
        }

        Array2D operator+(const Array2D& ob){
            if(rows == ob.rows && cols == ob.cols){
                Array2D temp(rows, cols);
                for(int i = 0; i < rows; i++){
                    for(int j = 0; j < cols; j++){
                        temp[i][j] = ptr[i][j] + ob.ptr[i][j];
                    }
                }
                return temp;
            }
            else{
                cout << "Dimension mismatch for addition!" << endl;
                exit(1);
            }
        }

        Array2D operator-(const Array2D& ob){
            if(rows == ob.rows && cols == ob.cols){
                Array2D temp(rows, cols);
                for(int i = 0; i < rows; i++){
                    for(int j = 0; j < cols; j++){
                        temp[i][j] = ptr[i][j] - ob.ptr[i][j];
                    }
                }
                return temp;
            }
            else{
                cout << "Dimension mismatch for subtraction!" << endl;
                exit(1);
            }
        }

        Array2D operator*(const Array2D& ob){
            if(cols == ob.rows){
                Array2D temp(rows, ob.cols);
                for(int i = 0; i < rows; i++){
                    for(int j = 0; j < ob.cols; j++){
                        temp[i][j] = 0;
                        for(int k = 0; k < cols; k++){
                            temp[i][j] += ptr[i][k] * ob.ptr[k][j];
                        }
                    }
                }
                return temp;
            }
            else{
                cout << "Dimension mismatch for multiplication!" << endl;
                exit(1);
            }
        }

        ~Array2D(){
            for(int i = 0; i < rows; i++){
                delete[] ptr[i];
            }
            delete[] ptr;
        }

        void display(){
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++){
                    cout << ptr[i][j] << "\t";
                }
                cout << endl;
            }
        }
};

int main(){
    Array2D m1(2, 2), m2(2, 2);

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            m1[i][j] = i + j + 1;
            m2[i][j] = (i + 1) * 2;
        }
    }

    cout << "Matrix 1:" << endl;
    m1.display();

    cout << "Matrix 2:" << endl;
    m2.display();

    Array2D mSum = m1 + m2;
    cout << "Matrix Sum (m1 + m2):" << endl;
    mSum.display();

    Array2D mProd = m1 * m2;
    cout << "Matrix Product (m1 * m2):" << endl;
    mProd.display();

    return 0;
}

