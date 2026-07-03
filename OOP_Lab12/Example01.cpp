#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream myfile("file1.txt");
    if (!myfile) {
        cout << "File not created!";
    } else {
        cout << "File created successfully!";
        myfile.close();
    }
    return 0;
}

