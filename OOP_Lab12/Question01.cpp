#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    char str[100];
    cout << "Enter a string: ";
    cin.getline(str, 100);

    int len = strlen(str);
    cout << "Length: " << len << endl;

    // Write to file
    ofstream fout("string.txt");
    fout << str;
    fout.close();

    // Read from file
    char ch;
    ifstream fin("string.txt");
    cout << "Stored characters: ";
    while (fin.get(ch)) {
        cout << ch;
    }
    fin.close();

    return 0;
}
