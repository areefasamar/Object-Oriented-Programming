#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream fout("source.txt");
    fout << "This is the source file content.";
    fout.close();

    ifstream fin("source.txt");
    ofstream fcopy("destination.txt");

    char ch;
    while (fin.get(ch)) {
        fcopy.put(ch);
    }

    fin.close();
    fcopy.close();

    cout << "File copied successfully!" << endl;
    return 0;
}

