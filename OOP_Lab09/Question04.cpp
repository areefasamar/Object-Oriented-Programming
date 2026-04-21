#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class EncryptionTecnique {
    public:
        virtual ~EncryptionTecnique() {}
        
        virtual void encrypt(string msg) = 0;
};

class EncryptionTecnique1 : public EncryptionTecnique {
    public:
        void encrypt(string msg) {
                cout << "Encrypted using Technique 1: ";
                for (int i = 0; i < msg.length(); i++) {
                        char c = toupper(msg[i]);
                        cout << (int)c;
                }
                cout << endl;
        }
};

class EncryptionTecnique2 : public EncryptionTecnique {
    public:
        void encrypt(string msg) {
                cout << "Encrypted using Technique 2: ";
                for (int i = 0; i < msg.length(); i++) {
                        char c = toupper(msg[i]);
                        cout << (int)c + 2;
                }
                cout << endl;
        }
};

int main(void) {
        string message;
        
        cout << "Enter a message to encrypt: ";
        cin >> message;

        cout << "\nOriginal Message: " << message << endl;

        EncryptionTecnique* tech1 = new EncryptionTecnique1();
        EncryptionTecnique* tech2 = new EncryptionTecnique2();

        tech1->encrypt(message);
        tech2->encrypt(message);

        delete tech1;
        delete tech2;

        return 0;
}


