#include<iostream>
#include<cstdlib>
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

        // Copy Constructor (Required for passing by value)
        Array(const Array& ob){
            size = ob.size;
            ptr = new int[size];
            for(int i = 0; i < size; i++){
                ptr[i] = ob.ptr[i];
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

        // Destructor
        ~Array(){
            delete[] ptr;
        }

        friend int dotproduct(Array, Array);
};

// Friend function for dot product
int dotproduct(Array a1, Array a2){
    if(a1.size == a2.size){
        int temp = 0;
        for(int i = 0; i < a1.size; i++)
            temp += a1[i] * a2[i];
        return temp;
    }
    else{
        cout << "Size mismatch error" << endl;
        exit(1);
    }
}

int main(){
    Array a1(5), a2(5);

    for(int i = 0; i < 5; i++){
        a1[i] = i * 2;
        a2[i] = i + 3;
    }

    cout << "Array 1 elements:" << endl;
    for (int i = 0; i < 5; i++)
        cout << a1[i] << endl;

    cout << "Array 2 elements:" << endl;
    for (int i = 0; i < 5; i++)
        cout << a2[i] << endl;

    cout << "Dot Product result:" << endl;
    cout << dotproduct(a1, a2) << endl;

    return 0;
}