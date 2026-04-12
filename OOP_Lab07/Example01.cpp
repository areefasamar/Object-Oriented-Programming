#include<iostream>
#include <cstdlib>
using namespace std;

class Array{
    int size;
    int *ptr;

    public:
        // Constructor
        Array(int s = 0) : size(s), ptr(NULL){
            if(size > 0){
                ptr = new int[size];
                if(ptr == NULL){
                    exit(1);
                }
            }
        }

        // Copy Constructor
        Array(const Array& ob){
            if(ob.size > 0){
                size = ob.size;
                ptr = new int[size];
                if(ptr == NULL){
                    exit(1);
                }
                for(int i = 0; i < size; i++){
                    ptr[i] = ob.ptr[i];
                }
            }
            else{
                size = 0;
                ptr = NULL;
            }
        }

        // Subscript operator
        int& operator[](int in){
            if(in >= size || in < 0){
                cout << "index " << in << " is out of bound" << endl;
                exit(1);
            }
            return ptr[in];
        }

        // Addition operator (Array + Array)
        Array operator+(Array& ob){
            if (size == ob.size){
                Array temp(size);
                for(int i = 0; i < size; i++)
                    temp[i] = ptr[i] + ob[i];
                return temp;
            }
            else{
                cout << "The size of array does not match!" << endl;
                exit(1);
            }
        }

        // Multiplication operator (Dot Product)
        int operator*(Array& ob){
            if (size == ob.size){
                int temp = 0;
                for(int i = 0; i < size; i++)
                    temp += ptr[i] * ob[i];
                return temp;
            }
            else{
                cout << "The size of array does not match!" << endl;
                exit(1);
            }
        }

        // Destructor
        ~Array(){
            delete[] ptr;
        }
};

int main(){
    Array a1(5), a2(5);

    for(int i = 0; i < 5; i++){
        a1[i] = i * 2;
        a2[i] = i + 3;
    }

    cout << "Array 1 elements:" << endl;
    for (int i = 0; i < 5; i++)
        cout << a1[i] << " ";
    cout << endl;

    cout << "Array 2 elements:" << endl;
    for (int i = 0; i < 5; i++)
        cout << a2[i] << " ";
    cout << endl;

    Array a3(a1);
    Array a4 = a1 + a2;

    cout << "Array 4 (Sum of a1 and a2):" << endl;
    for(int i = 0; i < 5; i++)
        cout << a4[i] << "\t";
    cout << endl;

    cout << "Dot product of a1 and a2:" << endl;
    cout << a1 * a2 << endl;

    return 0;
}
