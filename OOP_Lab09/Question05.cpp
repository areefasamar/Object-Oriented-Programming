#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class EncryptionTecnique {
    public:
        virtual ~EncryptionTecnique() {}
        virtual string encrypt(string msg) = 0;
};

class EncryptionTecnique1 : public EncryptionTecnique {
    public:
        string encrypt(string msg) {
                string result = "";
                for (int i = 0; i < msg.length(); i++) {
                        char c = toupper(msg[i]);
                        result += to_string((int)c);
                }
                return result;
        }
};

class EncryptionTecnique2 : public EncryptionTecnique {
    public:
        string encrypt(string msg) {
                string result = "";
                for (int i = 0; i < msg.length(); i++) {
                        char c = toupper(msg[i]);
                        result += to_string((int)c + 2);
                }
                return result;
        }
};

class DecryptionTecnique {
    public:
        virtual ~DecryptionTecnique() {}
        virtual string decrypt(string encryptedMsg) = 0;
};

class DecryptionTecnique1 : public DecryptionTecnique {
    public:
        string decrypt(string encryptedMsg) {
                string result = "";
                for (int i = 0; i < encryptedMsg.length(); i += 2) {
                        string code = encryptedMsg.substr(i, 2);
                        int asciiVal = stoi(code);
                        result += (char)asciiVal;
                }
                return result;
        }
};

class DecryptionTecnique2 : public DecryptionTecnique {
    public:
        string decrypt(string encryptedMsg) {
                string result = "";
                for (int i = 0; i < encryptedMsg.length(); i += 2) {
                        string code = encryptedMsg.substr(i, 2);
                        int asciiVal = stoi(code) - 2;
                        result += (char)asciiVal;
                }
                return result;
        }
};

int main(void) {
        string message;

        cout << "Enter a message to encrypt and decrypt: ";
        cin >> message;
        cout << "\nOriginal Message: " << message << endl;

        EncryptionTecnique* enc1 = new EncryptionTecnique1();
        EncryptionTecnique* enc2 = new EncryptionTecnique2();

        string encrypted1 = enc1->encrypt(message);
        string encrypted2 = enc2->encrypt(message);

        cout << "\nEncrypted using Technique 1: " << encrypted1 << endl;
        cout << "Encrypted using Technique 2: " << encrypted2 << endl;

        DecryptionTecnique* dec1 = new DecryptionTecnique1();
        DecryptionTecnique* dec2 = new DecryptionTecnique2();

        string decrypted1 = dec1->decrypt(encrypted1);
        string decrypted2 = dec2->decrypt(encrypted2);

        cout << "\nDecrypted using Technique 1: " << decrypted1 << endl;
        cout << "Decrypted using Technique 2: " << decrypted2 << endl;

        delete enc1;
        delete enc2;
        delete dec1;
        delete dec2;

        return 0;
}

