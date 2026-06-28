#include <iostream>
#include <fstream>
using namespace std;

class Participant {
public:
    int id, score;
    char name[50];

    void Input() {
        cout << "Enter ID: "; cin >> id;
        cout << "Enter Name: "; cin >> name;
        cout << "Enter Score: "; cin >> score;

        ofstream fout("participant.dat", ios::binary | ios::app);
        fout.write((char*)this, sizeof(*this));
        fout.close();
    }

    void Output() {
        int searchId;
        cout << "Enter ID to search: "; cin >> searchId;

        Participant temp;
        ifstream fin("participant.dat", ios::binary);
        bool found = false;
        while (fin.read((char*)&temp, sizeof(temp))) {
            if (temp.id == searchId) {
                cout << "Name: " << temp.name << ", Score: " << temp.score << endl;
                found = true;
                break;
            }
        }
        fin.close();
        if (!found) cout << "ID not found." << endl;
    }

    void Max() {
        Participant temp;
        ifstream fin("participant.dat", ios::binary);
        int maxScore = -1;
        char maxName[50];

        while (fin.read((char*)&temp, sizeof(temp))) {
            if (temp.score > maxScore) {
                maxScore = temp.score;
                strcpy(maxName, temp.name);
            }
        }
        fin.close();
        cout << "Highest Score: " << maxName << " with " << maxScore << endl;
    }
};

int main() {
    Participant p;
    int choice;
    cout << "1. Input  2. Output  3. Max\nChoice: ";
    cin >> choice;

    if (choice == 1) p.Input();
    else if (choice == 2) p.Output();
    else p.Max();

    return 0;
}

