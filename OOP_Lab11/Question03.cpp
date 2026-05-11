#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

void Sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of integers (N): ";
    cin >> n;

    vector<int> original;
    cout << "Enter " << n << " integers:" << endl;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        original.push_back(val);
    }

    const int iterations = 1000;

    auto start1 = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        vector<int> temp = original;
        Sort(temp);
    }
    auto stop1 = high_resolution_clock::now();
    auto total_ns1 = duration_cast<nanoseconds>(stop1 - start1).count();

    auto start2 = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        vector<int> temp = original;
        sort(temp.begin(), temp.end());
    }
    auto stop2 = high_resolution_clock::now();
    auto total_ns2 = duration_cast<nanoseconds>(stop2 - start2).count();

    cout << "\n--- Timing Results ---" << endl;
    cout << "Custom Sort Time: " << total_ns1 / iterations << " nanoseconds" << endl;
    cout << "STL Sort Time:    " << total_ns2 / iterations << " nanoseconds" << endl;

    vector<int> finalSorted = original;
    sort(finalSorted.begin(), finalSorted.end());
    
    cout << "\nSorted Order: ";
    for (int x : finalSorted) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
