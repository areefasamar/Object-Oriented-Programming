#include <iostream>
using namespace std;

int main() {
        try {
                throw 10;
        }
        catch (char excp) {
                cout << "Caught char: " << excp << endl;
        }
        catch (...) {
                cout << "Default Exception " << endl;
        }

        return 0;
}



