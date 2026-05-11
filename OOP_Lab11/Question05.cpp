#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
        set<string> guestList;
        string name;
        char choice;

        cout << "--- Party Guest List Manager ---" << endl;

        do {
                cout << "\nEnter guest name: ";
                getline(cin >> ws, name); 

                auto result = guestList.insert(name);

                if (result.second) {
                        cout << "Success: " << name << " added to the list." << endl;
                } else {
                        cout << "Note: " << name << " is already on the list (duplicate ignored)." << endl;
                }

                cout << "Add another guest? (y/n): ";
                cin >> choice;

        } while (choice == 'y' || choice == 'Y');

        cout << "\n--- Final Unique Guest List (Alphabetical) ---" << endl;
        if (guestList.empty()) {
                cout << "The list is empty." << endl;
        } else {
                for (const string& guest : guestList) {
                        cout << "- " << guest << endl;
                }
                
                cout << "\nTotal number of unique guests: " << guestList.size() << endl;
        }

        cout << "\nThank you for using the Guest Manager!" << endl;

        return 0;
}

