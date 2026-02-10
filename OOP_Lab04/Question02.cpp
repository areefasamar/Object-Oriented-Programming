#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* arr;     
    int capacity; 
    int count;    
public:
    DynamicArray(int size) {
        capacity = size;
        arr = new int[capacity];
        count = 0;
        for(int i = 0; i < capacity; i++) {
            arr[i] = 0;
        }
    }

    void add(int value) {
        if(count < capacity) {
            arr[count] = value;
            count++;
        } else {
            cout << "Array is full! Cannot add more elements." << endl;
        }
    }

    int size() const {
        return count;
    }

    void display() const {
        for(int i = 0; i < count; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    ~DynamicArray() {
        delete[] arr;
    }
};

int main() {
    DynamicArray arr(5); 

    arr.add(10);
    arr.add(20);
    arr.add(30);

    cout << "Array elements: ";
    arr.display();

    cout << "Current size: " << arr.size() << endl;

    arr.add(40);
    arr.add(50);
    arr.add(60); 

    cout << "Array elements: ";
    arr.display();
    cout << "Current size: " << arr.size() << endl;

    return 0;
}
