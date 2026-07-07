#include <iostream>
#include <fstream>
using namespace std;

bool fileExists(const string& filePath) {
    ifstream file(filePath);
    return file.good();
}

bool canAccessFile(const string& filePath) {
    ifstream file(filePath);
    return file.is_open();
}

int main() {
    string filePath = "file1.txt";

    if (fileExists(filePath)) {
        if (canAccessFile(filePath)) {
            cout << "File exists and can be accessed." << endl;
            ifstream file(filePath);
            // perform operations...
        } else {
            cout << "Cannot access the file." << endl;
        }
    } else {
        cout << "File does not exist." << endl;
    }

    return 0;
}

