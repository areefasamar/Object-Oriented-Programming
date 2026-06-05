#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class Median {
private:
    int size;
    T* array;

public:
    Median(T* a = NULL, int s = 0) {
        array = a;
        size = s;
    }

    double getMedian() {

        sort(array, array + size);

        if (size % 2 == 0) {
            return (array[size / 2] + array[(size / 2) - 1]) / 2.0;
        }

        else {
            return array[size / 2];
        }
    }
};

int main() {

    int array[] = {5, 1, 3, 2, 4};

    Median<int> obj(array, 5);

    cout << "Median = " << obj.getMedian() << endl;

    return 0;
}