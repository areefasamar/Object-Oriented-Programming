#include <iostream>
#include <string>

using namespace std;

// --- 1. THE GENERAL TEMPLATE ---
// This handles standard math logic for basic numbers (int, double, float, etc.)
template <typename T, typename U>
class Adder {
public:
    static void performAdd(T a, U b) {
        cout << "General Addition Match: " << (a + b) << "\n";
    }
};

// --- 2. TRUE PARTIAL SPECIALIZATION ---
// First type 'T' remains completely flexible ("as it is") up top.
// Second type slot is permanently fixed to a 'string'.
template <typename T>
class Adder<T, string> {
public:
    static void performAdd(T a, string b) {
        // Using to_string() so any numeric type T can safely merge with the string
        cout << "Partial Specialization Match (Any Type + String): " << to_string(a) + b << "\n";
    }
};

// --- 3. FULL SPECIALIZATION ---
// Both slots are permanently hardcoded to 'string'. 
// No template parameters are left open, so the top brackets are empty.
template <>
class Adder<string, string> {
public:
    static void performAdd(string a, string b) {
        cout << "Full Specialization Match (String + String): " << (a + b) << "\n";
    }
};

// --- MAIN EXECUTION ---
int main() {
    // Case A: Triggers General Template (int + int)
    Adder<int, int>::performAdd(40, 2); 

    // Case B: Triggers General Template (double + double)
    Adder<double, double>::performAdd(1.5, 2.5); 

    // Case C: Triggers Partial Specialization!
    // The second type is a string, but the first type is flexibly deduced as an int.
    Adder<int, string>::performAdd(40, "Hz"); 

    // Case D: Triggers Partial Specialization!
    // The second type is a string, but the first type is flexibly deduced as a double.
    Adder<double, string>::performAdd(9.8, " m/s^2"); 

    // Case E: Triggers Full Specialization!
    // Both types match the strict string requirement.
    Adder<string, string>::performAdd("C++ ", "Templates"); 

    return 0;
}