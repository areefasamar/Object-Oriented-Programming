#include "PasswordGenerator.h"
#include "PasswordVault.h"
#include "WinCompat.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
using namespace std;

// Color helpers (only used in this file)
static void genSetColor(int code) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), code);
}
static void genResetColor() { genSetColor(7); }


// ─────────────────────────────────────────────
//  BASE CLASS — PasswordGenerator
// ─────────────────────────────────────────────

PasswordGenerator::PasswordGenerator(int len, bool upper, bool digits,
                                     bool symbols, bool avoidConfusing)
    : length(len), useUppercase(upper), useDigits(digits),
      useSymbols(symbols), avoidLookAlikes(avoidConfusing) {}

void PasswordGenerator::setLength(int len) {
    if (len < 4 || len > 64) {
        throw invalid_argument("Length must be between 4 and 64.");
    }
    length = len;
}

void PasswordGenerator::setUseUppercase(bool val)    { useUppercase    = val; }
void PasswordGenerator::setUseDigits(bool val)       { useDigits       = val; }
void PasswordGenerator::setUseSymbols(bool val)      { useSymbols      = val; }
void PasswordGenerator::setAvoidLookAlikes(bool val) { avoidLookAlikes = val; }
int  PasswordGenerator::getLength() const            { return length;         }


// ─────────────────────────────────────────────
//  SUBCLASS 1 — RandomGenerator
// ─────────────────────────────────────────────

RandomGenerator::RandomGenerator(int len, bool upper, bool digits,
                                 bool symbols, bool avoidConfusing)
    : PasswordGenerator(len, upper, digits, symbols, avoidConfusing) {}

string RandomGenerator::buildCharPool() {
    string pool = "abcdefghijkmnopqrstuvwxyz";

    if (avoidLookAlikes) {
        string cleaned = "";
        for (char c : pool) {
            if (c != 'o') cleaned += c;
        }
        pool = cleaned;
    }

    if (useUppercase) {
        if (avoidLookAlikes) {
            pool += "ABCDEFGHJKLMNPQRSTUVWXYZ";
        } else {
            pool += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        }
    }

    if (useDigits) {
        pool += avoidLookAlikes ? "23456789" : "0123456789";
    }

    if (useSymbols) {
        pool += "@#$!%&*";
    }

    return pool;
}

string RandomGenerator::generate() {
    string pool = buildCharPool();

    if (pool.empty()) {
        throw runtime_error("Character pool is empty. Enable at least one character type.");
    }

    static bool seeded = false;
    if (!seeded) { srand((unsigned int)time(0)); seeded = true; }

    string password = "";
    for (int i = 0; i < length; i++) {
        int index = rand() % pool.size();
        password += pool[index];
    }

    return password;
}


// ─────────────────────────────────────────────
//  SUBCLASS 2 — PhraseGenerator
// ─────────────────────────────────────────────

PhraseGenerator::PhraseGenerator(int words, char sep)
    : PasswordGenerator(12, false, false, false, false),
      wordCount(words), separator(sep) {}

void PhraseGenerator::setWordCount(int words) {
    if (words < 2 || words > 4) {
        throw invalid_argument("Word count must be 2, 3, or 4.");
    }
    wordCount = words;
}

void PhraseGenerator::setSeparator(char sep) {
    separator = sep;
}

string PhraseGenerator::generate() {
    static bool seeded = false;
    if (!seeded) { srand((unsigned int)time(0)); seeded = true; }

    string words[] = {
        "Blue", "Tiger", "Storm", "Cloud", "River", "Eagle", "Stone", "Flame",
        "Swift", "Night", "Brave", "Solar", "Frost", "Cedar", "Maple", "Ocean",
        "Pixel", "Lunar", "Amber", "Steel", "Crisp", "Vivid", "Blaze", "Delta",
        "Flint", "Shadow", "Glacier", "Summit", "Zenith", "Orbit", "Pulse", "Canyon",
        "Prism", "Echo", "Falcon", "Gully", "Harbor", "Jungle", "Kite", "Legend",
        "Mist", "Nomad", "Onyx", "Panda", "Quartz", "Radar", "Siren", "Tulip",
        "Under", "Vortex", "Willow", "Xenon", "Yacht", "Zebra", "Alpha", "Beta"
    };
    int wordListSize = 56;

    string passphrase = "";

    for (int i = 0; i < wordCount; i++) {
        int index = rand() % wordListSize;
        passphrase += words[index];

        if (i < wordCount - 1) {
            passphrase += separator;
        }
    }

    int num = 10 + rand() % 90;
    passphrase += to_string(num);

    return passphrase;
}


// ─────────────────────────────────────────────
//  HELPER — read a valid yes/no answer
// ─────────────────────────────────────────────
bool askYesNo(const string& question) {
    string input;
    while (true) {
        cout << question << " (y/n): ";
        cin >> input;
        cin.ignore(1000, '\n');

        if (input == "y" || input == "Y" || input == "yes" || input == "YES") return true;
        if (input == "n" || input == "N" || input == "no"  || input == "NO")  return false;

        cout << "  Invalid input. Please enter y or n.\n";
    }
}

// ─────────────────────────────────────────────
//  HELPER — read an integer within a range
// ─────────────────────────────────────────────
int askInt(const string& question, int minVal, int maxVal) {
    string input;
    while (true) {
        cout << question;
        cin >> input;
        cin.ignore(1000, '\n');

        bool valid = !input.empty();
        for (char c : input) {
            if (!isdigit(c)) { valid = false; break; }
        }

        if (valid) {
            int value = stoi(input);
            if (value >= minVal && value <= maxVal) return value;
        }

        cout << "  Invalid input. Please enter a number between "
             << minVal << " and " << maxVal << ".\n";
    }
}

// ─────────────────────────────────────────────
//  FREE FUNCTION — runPasswordGenerator
// ─────────────────────────────────────────────
string runPasswordGenerator() {
    system("cls");
    genSetColor(11);
    cout << "\n  ========================================\n";
    cout << "           PASSWORD GENERATOR\n";
    cout << "  ========================================\n\n";
    genResetColor();

    genSetColor(8);
    cout << "  Do you need to remember this password, or will it be saved in the vault?\n";
    genResetColor();
    genSetColor(14); cout << "    [1]"; genResetColor(); cout << "  I need to remember it  (Phrase mode)\n";
    genSetColor(14); cout << "    [2]"; genResetColor(); cout << "  I will save it         (Random mode)\n\n";

    int modeChoice = askInt("  Enter choice: ", 1, 2);

    string generatedPassword = "";

    // PHRASE MODE
    if (modeChoice == 1) {
        PhraseGenerator pg;

        int words = askInt("\n  How many words? (2 / 3 / 4): ", 2, 4);
        pg.setWordCount(words);

        genSetColor(8);
        cout << "\n  Separator between words?\n";
        genResetColor();
        genSetColor(14); cout << "    [1]"; genResetColor(); cout << "  None   -- BlueStorm49\n";
        genSetColor(14); cout << "    [2]"; genResetColor(); cout << "  Dash   -- Blue-Storm-49\n";
        genSetColor(14); cout << "    [3]"; genResetColor(); cout << "  Symbol -- Blue$Storm$49\n";
        int sepChoice = askInt("  Enter choice: ", 1, 3);

        char sep = '\0';
        if (sepChoice == 2) sep = '-';
        if (sepChoice == 3) sep = '$';
        pg.setSeparator(sep);

        try {
            generatedPassword = pg.generate();
        } catch (exception& e) {
            genSetColor(12);
            cout << "\n  Error generating password: " << e.what() << "\n";
            genResetColor();
            return "";
        }
    }

    // RANDOM MODE
    else {
        genSetColor(8);
        cout << "\n  How strong does it need to be?\n";
        genResetColor();
        genSetColor(14); cout << "    [1]"; genResetColor(); cout << "  Basic   (good for low-risk accounts)\n";
        genSetColor(14); cout << "    [2]"; genResetColor(); cout << "  Strong  (recommended for personal accounts)\n";
        genSetColor(14); cout << "    [3]"; genResetColor(); cout << "  Maximum (banking, work, email)\n";
        int strength = askInt("  Enter choice: ", 1, 3);

        bool upper   = true;
        bool digits  = true;
        bool symbols = true;
        bool avoid   = false;
        int  len     = 12;

        if (strength == 1) {
            len     = askInt("\n  Password length (8 to 64): ", 8, 64);
            upper   = askYesNo("  Include uppercase letters? (A-Z)");
            digits  = askYesNo("  Include numbers?           (0-9)");
            symbols = askYesNo("  Include symbols?           (@#$!)");
            avoid   = askYesNo("  Avoid look-alike characters? (0/O, 1/l)");

        } else if (strength == 2) {
            len = askInt("\n  Password length (12 to 64, recommended 16): ", 12, 64);

        } else {
            len = 20;
            genSetColor(14);
            cout << "\n  Maximum mode: All character types enabled. Length set to 20.\n";
            genResetColor();
        }

        if (!upper && !digits && !symbols) {
            genSetColor(14);
            cout << "\n  Note: Only lowercase letters will be used.\n";
            genResetColor();
        }

        RandomGenerator rg(len, upper, digits, symbols, avoid);

        try {
            generatedPassword = rg.generate();
        } catch (exception& e) {
            genSetColor(12);
            cout << "\n  Error generating password: " << e.what() << "\n";
            genResetColor();
            return "";
        }
    }

    genSetColor(10);
    cout << "\n  ----------------------------------------\n";
    cout << "    Generated Password:  " << generatedPassword << "\n";
    cout << "  ----------------------------------------\n";
    genResetColor();

    // SAVE TO VAULT (Random mode only)
    if (modeChoice == 2) {
        genSetColor(8);
        cout << "\n  Would you like to save this password to your vault? (y/n): ";
        genResetColor();
        string saveChoice;
        cin >> saveChoice;
        cin.ignore(1000, '\n');

        if (saveChoice == "y" || saveChoice == "Y") {
            string vaultName;
            genSetColor(8); cout << "  Enter vault name (e.g., work, personal): "; genResetColor();
            getline(cin, vaultName);

            if (vaultName.empty()) {
                genSetColor(12); cout << "  Invalid vault name.\n"; genResetColor();
            } else {
                string masterPass;
                genSetColor(8); cout << "  Enter your master password: "; genResetColor();
                cin >> masterPass;
                cin.ignore(1000, '\n');

                PasswordVault vault;
                if (vault.open(vaultName, masterPass)) {
                    string label;
                    genSetColor(8); cout << "\n  Enter a label for this password (e.g., Gmail, Bank): "; genResetColor();
                    getline(cin, label);

                    if (!label.empty()) {
                        vault.saveEntry(label, generatedPassword);
                        genSetColor(10);
                        cout << "\n  [OK] Password saved to vault successfully!\n";
                        genResetColor();
                    } else {
                        genSetColor(12); cout << "  Invalid label. Password not saved.\n"; genResetColor();
                    }
                } else {
                    if (vault.isVaultLocked()) {
                        genSetColor(12);
                        cout << "\n  Too many failed attempts. Vault locked for 30 seconds.\n";
                        genResetColor();
                    } else {
                        genSetColor(12);
                        cout << "\n  [ERROR] Wrong master password or vault not found.\n";
                        genResetColor();
                    }
                }
            }
        }
    }

    genSetColor(8);
    cout << "\n  Tip: You can evaluate this password using Option 1 from the main menu.\n";
    genResetColor();
    cout << "\n  Press Enter to return to menu...";
    cin.ignore(1000, '\n');

    return generatedPassword;
}
