#include <iostream>
#include <fstream>
using namespace std;
int main() {
    char data[100];
    // Write to file
    ofstream outfile;
    outfile.open("array.dat");

    cout << "Writing to the file" << endl;
    cout << "Enter your name: ";
    cin.getline(data, 100);
    outfile << data << endl;

    cout << "Enter your age: ";
    cin >> data;
    cin.ignore();
    outfile << data << endl;

    outfile.close();

    // Read from file
    ifstream infile;
    infile.open("array.dat");

    cout << endl << "Reading data from file" << endl;
    infile >> data;
    cout << "Name: " << data << endl;

    infile >> data;
    cout << "Age: " << data << endl;

    infile.close();

    return 0;
}


