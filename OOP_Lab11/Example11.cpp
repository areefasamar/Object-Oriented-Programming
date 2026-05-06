#include <iostream>
#include <map>
using namespace std;

int main() {
        map<string, int> m;

        m["one"] = 1;
        m["two"] = 2;
        m["three"] = 3;

        map<string, int>::iterator it = m.begin();

        while (it != m.end()) {
                cout << "Key: " << it->first << ", Value: " << it->second << endl;
                ++it;
        }

        return 0;
}

