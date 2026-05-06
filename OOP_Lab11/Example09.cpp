#include <iostream>
#include <vector>
using namespace std;

int main() {
        vector<int> prime_numbers{2, 3, 5, 7};

        cout << "Initial Vector: ";
        for (int i : prime_numbers) {
                cout << i << " ";
        }

        prime_numbers.pop_back();

        cout << "\nUpdated Vector: ";
        for (int i : prime_numbers) {
                cout << i << " ";
        }

        return 0;
}

