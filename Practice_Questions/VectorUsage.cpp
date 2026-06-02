#include <iostream>
#include <vector>
#include <algorithm> // Required for std::find

using namespace std;

void displayVector(const vector<int>& v) {
    cout << "Vector elements: ";
    for (int x : v) {
        cout << x << " ";
    }
    cout << " | Size: " << v.size() << endl;
    cout << "-----------------------------------------------" << endl;
}

int main() {
    // Creating an empty vector
    vector<int> vec;

    // 1. PUSH: Adding elements to the end
    cout << "--- Pushing Elements (10, 20, 30, 40) ---" << endl;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    displayVector(vec);

    // 2. POP: Removing the last element
    cout << "--- Popping Last Element (Removes 40) ---" << endl;
    vec.pop_back();
    displayVector(vec);

    // 3. SIZE: Getting the current size
    cout << "Current Vector Size: " << vec.size() << endl << endl;

    // 4. FIND: Searching for an element
    cout << "--- Finding Element 20 ---" << endl;
    // std::find returns an iterator (a pointer-like object)
    auto it = find(vec.begin(), vec.end(), 20);

    if (it != vec.end()) {
        // Distance calculates the index from the beginning
        cout << "Found 20 at index: " << distance(vec.begin(), it) << endl;
    } else {
        cout << "Element not found." << endl;
    }
    cout << "-----------------------------------------------" << endl;

    // 5. ERASE: Removing elements using Iterators
    
    // Scenario A: Erase by specific index (e.g., index 0, which is '10')
    cout << "--- Erasing Element at Index 0 (Removes 10) ---" << endl;
    vec.erase(vec.begin() + 0); 
    displayVector(vec);

    // Scenario B: Erase a specific value found by std::find
    cout << "--- Finding and Erasing Value 30 ---" << endl;
    auto findTarget = find(vec.begin(), vec.end(), 30);
    if (findTarget != vec.end()) {
        vec.erase(findTarget); // Erases the element where the iterator is pointing
    }
    displayVector(vec);

    return 0;
}