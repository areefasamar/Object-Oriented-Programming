#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>

using namespace std;

class PasswordException : public exception {
        private:
                string message;
        public:
                PasswordException(string msg) : message(msg) {}

                const char* what() const noexcept override {
                        return message.c_str();
                }
};

void validatePassword(string password) {
        bool hasDigit = false;

        if (password.length() < 6) {
                throw PasswordException("Error: Password must be at least 6 characters long!");
        }

        for (char ch : password) {
                if (isdigit(ch)) {
                        hasDigit = true;
                        break;
                }
        }

        if (!hasDigit) {
                throw PasswordException("Error: Password must contain at least one digit (0-9)!");
        }
}

int main() {
        string username, password;

        cout << "--- Login System ---" << endl;
        cout << "Enter Username: ";
        getline(cin, username);

        cout << "Enter Password: ";
        getline(cin, password);

        try {
                validatePassword(password);
                cout << "Login successful! Welcome, " << username << "." << endl;
        }
        catch (const PasswordException& e) {
                cout << "Login Failed: " << e.what() << endl;
        }
        catch (const exception& e) {
                cout << "An unexpected error occurred: " << e.what() << endl;
        }

        return 0;
}


