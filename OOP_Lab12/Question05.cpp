#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // Create the file first (for testing)
    ofstream fout("STORY.TXT");
    fout << "The rose is red.\n";
    fout << "A girl is playing there.\n";
    fout << "There is a playground.\n";
    fout << "An airplane is in the sky.\n";
    fout << "Numbers are not allowed in the password.\n";
    fout.close();

    // Count lines not starting with 'A'
    ifstream fin("STORY.TXT");
    string line;
    int count = 0;

    while (getline(fin, line)) {
        if (!line.empty() && line[0] != 'A') {
            count++;
        }
    }
    fin.close();

    cout << "Lines not starting with 'A': " << count << endl;
    // Output: 3
    return 0;
}

