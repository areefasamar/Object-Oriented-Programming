#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream openFile("file2.txt");
    char ch;
    
    if (!openFile) {
        cout << "No such file";
    } else {
        while (!openFile.eof()) {
            openFile.get(ch);
            cout << ch;
        }
    }
    
    openFile.close();
    return 0;
}

