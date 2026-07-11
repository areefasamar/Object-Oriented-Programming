#include <iostream>
#include <fstream>
using namespace std;

int main() {
    fstream my_file;
    my_file.open("file2.txt", ios::in);
    
    if (!my_file) {
        cout << "No such file";
    } else {
        string line;
        while (!my_file.eof()) {
            getline(my_file, line);
            cout << line << endl;
        }
        my_file.close();
    }
    
    return 0;
}
