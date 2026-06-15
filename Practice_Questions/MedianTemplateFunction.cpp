#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
double getMedian(T* array, int size)
{
    sort(array, array + size);

    if (size % 2 == 0)
    {
        return (array[size / 2] + array[(size / 2) - 1]) / 2.0;
    }
    else
    {
        return array[size / 2];
    }
}

int main()
{
    int array[] = {5, 1, 3, 2, 4};

    cout << "Median = " << getMedian(array, 5) << endl;

    return 0;
}