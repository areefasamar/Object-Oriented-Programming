#include <iostream>
#include <string>

using namespace std;

// ─── CLASS 1: THE SIMPLE EXCEPTION CLASS ───
class MyException {
private:
    string errorMessage;

public:
    MyException(string msg) : errorMessage(msg) {}

    // Single simple getter to read the message
    string getMessage() const { return errorMessage; }
};


// ─── CLASS 2: THE WORKING CLASS ───
class ThermalRegulator {
public:
    void configureTemperature(int temp) {
        cout << "Attempting to set system temperature to: " << temp << "°C\n";
        
        if (temp > 100) {
            // ✅ Simple Named Object Method: Create 'e' with just a message, then throw it
            MyException e("Critical Overheating Danger!"); 
            throw e; 
        }
        
        cout << "Temperature successfully configured.\n\n";
    }
};


// ─── MAIN EXECUTION ───
int main() {
    ThermalRegulator regulator;

    try {
        regulator.configureTemperature(180); // ⚠️ This will trigger the exception
    }
    catch (const MyException& e) { 
        cout << "[EMERGENCY INTERCEPTED]\n";
        cout << "Error: " << e.getMessage() << "\n";
    }

    cout << "\nProgram safely recovered and continues executing...\n";
    return 0;
}