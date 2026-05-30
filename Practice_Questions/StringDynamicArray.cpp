#include <iostream>
#include <cstring>   // For strlen and strcpy
#include <stdexcept> // For out_of_range exception

using namespace std;

class String {
private:
    char* str;
    int length;

public:
    // 1. Parametric Constructor: String(msg : const char*)
    String(const char* msg) {
        if (msg == nullptr) {
            length = 0;
            str = new char[1];
            str[0] = '\0';
        } else {
            length = strlen(msg);
            str = new char[length + 1];
            strcpy(str, msg);
        }
    }

    // 2. Copy Constructor: String(other : const String&)
    String(const String& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
    }

    // 3. Destructor: ~String()
    ~String() {
        delete[] str;
    }

    // 4. Character Access with Bounds Checking: getCharAt(index : int) : char
    char getCharAt(int index) const {
        if (index < 0 || index >= length) {
            // Exception handling for out-of-bounds access
            throw out_of_range("Index out of bounds exception!");
        }
        return str[index];
    }

    // 5. Concatenation Operator Overloading: operator+(other : const String&) : String
    String operator+(const String& other) const {
        // Allocate a temporary buffer to hold the combined strings
        int newLength = this->length + other.length;
        char* tempBuffer = new char[newLength + 1];
        
        strcpy(tempBuffer, this->str);
        strcat(tempBuffer, other.str);
        
        // Create a temporary String object to return
        String newString(tempBuffer);
        
        // Delete the temporary buffer to avoid a memory leak
        delete[] tempBuffer;
        
        return newString;
    }

    // 6. Comparison Operator Overloading: operator==(other : const String&) : bool
    bool operator==(const String& other) const {
        if (this->length != other.length) {
            return false;
        }
        return strcmp(this->str, other.str) == 0;
    }

    // 7. Display Method: display() : void
    void display() const {
        cout << str;
    }
};

// Demonstration of the implemented String class with error handling
int main() {
    try {
        cout << "--- String Initialization & Display ---" << endl;
        String s1("Hello ");
        String s2("World");
        
        cout << "s1: "; s1.display(); cout << endl;
        cout << "s2: "; s2.display(); cout << endl;

        cout << "\n--- Copy Constructor ---" << endl;
        String s3 = s2; // Calls Copy Constructor
        cout << "s3 (copied from s2): "; s3.display(); cout << endl;

        cout << "\n--- Concatenation (+) Operator ---" << endl;
        String s4 = s1 + s2; // Calls operator+
        cout << "s4 (s1 + s2): "; s4.display(); cout << endl;

        cout << "\n--- Comparison (==) Operator ---" << endl;
        if (s2 == s3) {
            cout << "s2 and s3 are equal." << endl;
        } else {
            cout << "s2 and s3 are not equal." << endl;
        }

        cout << "\n--- Bounds-Checked Character Access ---" << endl;
        cout << "Character at index 1 of s2: " << s2.getCharAt(1) << endl;

        cout << "\n--- Testing Exception Handling (Out of Bounds) ---" << endl;
        // This line intentionally triggers an index out of bounds error
        cout << "Character at index 20 of s2: " << s2.getCharAt(20) << endl;

    } 
    catch (const out_of_range& e) {
        // Catches the custom out_of_range error thrown by getCharAt()
        cerr << "\nCaught Exception: " << e.what() << endl;
    }

    return 0;
}