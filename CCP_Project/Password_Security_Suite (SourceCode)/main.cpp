#include "WinCompat.h"
#include <iostream>
#include <cstdlib>
#include "PasswordGenerator.h"
#include "PasswordEvaluator.h"
#include "PasswordVault.h"
#include "LeakChecker.h"
#include "HealthDashboard.h"
using namespace std;

// Defined in PasswordGenerator.cpp
string runPasswordGenerator();

// ── Colour helpers ────────────────────────────────────────────────────────────
static void setColor(int code) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), code);
}
static void resetColor() { setColor(7); }

// ─────────────────────────────────────────────────────────────────────────────
//  VAULT HELPER
//  Called by the vault menu and the health dashboard.
//  Creates a fresh PasswordVault, asks the user to authenticate,
//  handles lockout with a live countdown, and returns the vault by value.
//  Returns an open vault on success, or an unopened vault on failure.
// ─────────────────────────────────────────────────────────────────────────────
PasswordVault openVaultSession() {
    PasswordVault vault;

    setColor(11);
    cout << "\n  ---- Vault Access ----\n\n";
    resetColor();

    cout << "  [1] Create a new vault\n";
    cout << "  [2] Open an existing vault\n\n";

    int choice = askInt("  Enter choice: ", 1, 2);

    string vaultName;
    setColor(8); cout << "\n  Enter vault name (e.g. work, personal): "; resetColor();
    cin >> vaultName;
    cin.ignore(1000, '\n');

    if (vaultName.empty()) {
        setColor(12); cout << "\n  Vault name cannot be empty.\n"; resetColor();
        return vault;
    }

    // ── CREATE new vault ──────────────────────────────────────────────────────
    if (choice == 1) {
        if (MasterPasswordFile::exists(vaultName)) {
            setColor(12);
            cout << "\n  A vault named '" << vaultName << "' already exists.\n";
            cout << "  Use option [2] to open it.\n";
            resetColor();
            return vault;
        }

        string masterPwd;
        setColor(8); cout << "  Set a master password (8-20 characters): "; resetColor();
        cin >> masterPwd;
        cin.ignore(1000, '\n');

        if (masterPwd.size() < 8 || masterPwd.size() > 20) {
            setColor(12);
            cout << "\n  Master password must be 8 to 20 characters.\n";
            resetColor();
            return vault;
        }

        if (!vault.create(vaultName, masterPwd)) {
            setColor(12);
            cout << "\n  Failed to create vault. Check write permissions.\n";
            resetColor();
            return vault;
        }

        setColor(10);
        cout << "\n  Vault '" << vaultName << "' created successfully!\n";
        cout << "  Master password saved to registry (encrypted).\n";
        resetColor();
        Sleep(800);
        system("cls");
        return vault;
    }

    // ── OPEN existing vault ───────────────────────────────────────────────────
    else {
        if (!MasterPasswordFile::exists(vaultName)) {
            setColor(12);
            cout << "\n  No vault named '" << vaultName << "' found.\n";
            cout << "  Use option [1] to create it first.\n";
            resetColor();
            return vault;
        }

        // Allow up to 3 attempts — AuthGuard tracks the count internally.
        // After 3 fails AuthGuard sets isLocked = true for 30 seconds.
        for (int attempt = 1; attempt <= 3; attempt++) {
            // Check if already locked from a previous attempt
            if (vault.isVaultLocked()) {
                // Live countdown
                while (true) {
                    int remaining = vault.getLockRemainingTime();
                    if (remaining <= 0) break;
                    setColor(12);
                    cout << "\r  Vault locked. Please wait " << remaining
                         << " second(s)...   ";
                    resetColor();
                    cout.flush();
                    // Busy-wait 1 second
                    time_t start = time(0);
                    while (difftime(time(0), start) < 1.0) {}
                }
                setColor(14);
                cout << "\n\n  Lockout expired. You may try again.\n\n";
                resetColor();
                // Reset attempt counter after lockout expires
                attempt = 1;
            }

            string masterPwd;
            setColor(8);
            cout << "  Enter master password (attempt " << attempt << "/3): ";
            resetColor();
            cin >> masterPwd;
            cin.ignore(1000, '\n');

            if (vault.open(vaultName, masterPwd)) {
                setColor(10);
                cout << "\n  Vault '" << vaultName << "' opened.\n";
                resetColor();
                // Small pause so the success message is readable,
                // then clear before the vault menu renders — eliminates the flash.
                Sleep(600);
                system("cls");
                return vault;
            }

            // Wrong password
            if (vault.isVaultLocked()) {
                // Will be handled at top of loop
                continue;
            }

            int left = 3 - attempt;
            setColor(12);
            if (left > 0)
                cout << "  Wrong password. " << left << " attempt(s) remaining.\n";
            resetColor();
        }

        // If we reach here without returning, vault is locked
        setColor(12);
        cout << "\n  Too many failed attempts. Vault locked for 30 seconds.\n";
        resetColor();
        return vault;
    }
}

// ═════════════════════════════════════════════════════════════════════════════
//  FEATURE 1 — Password Evaluator
// ═════════════════════════════════════════════════════════════════════════════
void runPasswordEvaluator() {
    system("cls");
    setColor(11);
    cout << "\n  ========================================\n";
    cout << "       PASSWORD STRENGTH EVALUATOR\n";
    cout << "  ========================================\n";
    resetColor();

    PasswordEvaluator evaluator;
    char again = 'y';

    while (again == 'y' || again == 'Y') {
        string pwd = "";

        while (true) {
            setColor(8);
            cout << "\n  Enter password to evaluate: ";
            resetColor();
            cin >> pwd;
            cin.ignore(1000, '\n');

            try {
                evaluator.setPassword(pwd);
                break;
            }
            catch (invalid_argument& e) {
                setColor(12);
                cout << "  Error: " << e.what() << "\n";
                resetColor();
            }
        }

        try {
            evaluator.evaluate();
            evaluator.displayReport();
        }
        catch (runtime_error& e) {
            setColor(12);
            cout << "  Error: " << e.what() << "\n";
            resetColor();
        }

        setColor(8);
        cout << "  Evaluate another password? (y/n): ";
        resetColor();
        cin >> again;
        cin.ignore(1000, '\n');
    }
}

// ═════════════════════════════════════════════════════════════════════════════
//  FEATURE 2 — Password Generator
// ═════════════════════════════════════════════════════════════════════════════
void runGeneratorMenu() {
    string generated = runPasswordGenerator();
    (void)generated;
}

// ═════════════════════════════════════════════════════════════════════════════
//  FEATURE 3 — Password Vault
//  The vault is opened fresh every time this menu is entered.
//  It does NOT stay open between visits.
// ═════════════════════════════════════════════════════════════════════════════
void runVaultMenu() {
    system("cls");
    setColor(11);
    cout << "\n  ========================================\n";
    cout << "           PASSWORD VAULT\n";
    cout << "  ========================================\n\n";
    resetColor();

    PasswordVault vault = openVaultSession();

    if (!vault.getIsOpen()) {
        cout << "\n  Press Enter to continue...";
        cin.ignore(1000, '\n');
        return;
    }

    while (true) {
        system("cls");
        setColor(11);
        cout << "\n  ========================================\n";
        cout << "           PASSWORD VAULT\n";
        cout << "  ========================================\n";
        resetColor();
        setColor(10);
        cout << "  Entries: " << vault.getentryCount() << "\n\n";
        resetColor();

        setColor(14); cout << "  [1]"; resetColor(); cout << "  View all entries\n";
        setColor(14); cout << "  [2]"; resetColor(); cout << "  Add a new entry\n";
        setColor(14); cout << "  [3]"; resetColor(); cout << "  Search for an entry\n";
        setColor(14); cout << "  [4]"; resetColor(); cout << "  Delete an entry\n";
        setColor(12); cout << "  [0]"; resetColor(); cout << "  Back to main menu\n\n";

        int sub = askInt("  Enter choice: ", 0, 4);
        if (sub == 0) break;

        // ── View all ─────────────────────────────────────────────────────
        if (sub == 1) {
            system("cls");
            setColor(11);
            cout << "\n  ---- All Vault Entries ----\n\n";
            resetColor();

            vector<PasswordEntry> entries = vault.getAllEntries();
            if (entries.empty()) {
                setColor(14);
                cout << "  Vault is empty. Add some entries first!\n";
                resetColor();
            } else {
                for (int i = 0; i < (int)entries.size(); i++) {
                    setColor(14);
                    cout << "  [" << (i+1) << "] ";
                    resetColor();
                    cout << entries[i].getLabel();
                    setColor(8);
                    cout << "  (added: " << entries[i].getDateAdded() << ")\n";
                    resetColor();
                }

                cout << "\n  Enter number to reveal password, or 0 to go back: ";
                int sel = askInt("", 0, (int)entries.size());
                if (sel > 0) {
                    string plain = vault.decrypt(entries[sel-1].getEncryptedPassword());
                    cout << "\n";
                    setColor(10);
                    cout << "  Label    : " << entries[sel-1].getLabel()     << "\n";
                    cout << "  Added    : " << entries[sel-1].getDateAdded() << "\n";
                    cout << "  Password : " << plain                          << "\n";
                    resetColor();
                }
            }
            cout << "\n  Press Enter to continue...";
            cin.ignore(1000, '\n');
        }

        // ── Add entry ─────────────────────────────────────────────────────
        else if (sub == 2) {
            system("cls");
            setColor(11);
            cout << "\n  ---- Add New Entry ----\n\n";
            resetColor();

            string label, password;
            setColor(8); cout << "  Label (e.g. Gmail, Netflix): "; resetColor();
            getline(cin, label);

            if (label.empty()) {
                setColor(12); cout << "  Label cannot be empty.\n"; resetColor();
                cout << "  Press Enter to continue..."; cin.ignore(1000, '\n');
                continue;
            }

            setColor(8); cout << "  Password to save: "; resetColor();
            getline(cin, password);

            if (password.empty()) {
                setColor(12); cout << "  Password cannot be empty.\n"; resetColor();
                cout << "  Press Enter to continue..."; cin.ignore(1000, '\n');
                continue;
            }

            vault.saveEntry(label, password);
            setColor(10);
            cout << "\n  Entry '" << label << "' saved!\n";
            resetColor();
            cout << "  Press Enter to continue...";
            cin.ignore(1000, '\n');
        }

        // ── Search ────────────────────────────────────────────────────────
        else if (sub == 3) {
            system("cls");
            setColor(11);
            cout << "\n  ---- Search Entry ----\n\n";
            resetColor();

            string label;
            setColor(8); cout << "  Enter label to search: "; resetColor();
            getline(cin, label);

            const PasswordEntry* found = vault.searchEntry(label);
            if (found) {
                string plain = vault.decrypt(found->getEncryptedPassword());
                setColor(10);
                cout << "\n  Found!\n";
                cout << "  Label    : " << found->getLabel()     << "\n";
                cout << "  Added    : " << found->getDateAdded() << "\n";
                cout << "  Password : " << plain                  << "\n";
                resetColor();
            } else {
                setColor(12);
                cout << "\n  No entry found with label '" << label << "'.\n";
                resetColor();
            }
            cout << "\n  Press Enter to continue...";
            cin.ignore(1000, '\n');
        }

        // ── Delete ────────────────────────────────────────────────────────
        else if (sub == 4) {
            system("cls");
            setColor(11);
            cout << "\n  ---- Delete Entry ----\n\n";
            resetColor();

            string label;
            setColor(8); cout << "  Enter label to delete: "; resetColor();
            getline(cin, label);

            if (vault.deleteEntry(label)) {
                setColor(10);
                cout << "\n  Entry '" << label << "' deleted.\n";
            } else {
                setColor(12);
                cout << "\n  No entry found with label '" << label << "'.\n";
            }
            resetColor();
            cout << "  Press Enter to continue...";
            cin.ignore(1000, '\n');
        }
    }
}

// ═════════════════════════════════════════════════════════════════════════════
//  FEATURE 4 — Leaked Password Checker
// ═════════════════════════════════════════════════════════════════════════════
void runLeakChecker() {
    system("cls");
    setColor(11);
    cout << "\n  ========================================\n";
    cout << "      LEAKED PASSWORD CHECKER\n";
    cout << "  ========================================\n\n";
    resetColor();

    LeakChecker lc("leaked_passwords.txt");

    char again = 'y';
    while (again == 'y' || again == 'Y') {
        string password;
        setColor(8);
        cout << "  Enter a password to check: ";
        resetColor();
        cin >> password;
        cin.ignore(1000, '\n');

        if (password.empty()) {
            setColor(12); cout << "  Password cannot be empty.\n"; resetColor();
        } else {
            bool leaked = lc.isLeaked(password);
            cout << "\n  Result: ";
            if (leaked) {
                setColor(12);
                cout << "COMPROMISED!\n";
                resetColor();
                setColor(14);
                cout << "  This password was found in a known data breach.\n";
                cout << "  Do NOT use it anywhere. Change it immediately if in use.\n";
            } else {
                setColor(10);
                cout << "NOT found in the leak database.\n";
                resetColor();
                setColor(8);
                cout << "  (Still evaluate it with Option 1 to check its strength.)\n";
            }
            resetColor();
        }

        cout << "\n  Check another? (y/n): ";
        cin >> again;
        cin.ignore(1000, '\n');
    }
}

// ═════════════════════════════════════════════════════════════════════════════
//  FEATURE 5 — Vault Health Dashboard
// ═════════════════════════════════════════════════════════════════════════════
void runHealthDashboard() {
    system("cls");
    setColor(11);
    cout << "\n  ========================================\n";
    cout << "       VAULT HEALTH DASHBOARD\n";
    cout << "  ========================================\n\n";
    resetColor();

    // Ask for vault name only — no create option here
    string vaultName;
    setColor(8); cout << "  Enter vault name: "; resetColor();
    cin >> vaultName;
    cin.ignore(1000, '\n');

    if (vaultName.empty()) {
        setColor(12); cout << "\n  Vault name cannot be empty.\n"; resetColor();
        cout << "\n  Press Enter to continue...";
        cin.ignore(1000, '\n');
        return;
    }

    if (!MasterPasswordFile::exists(vaultName)) {
        setColor(12);
        cout << "\n  No vault named '" << vaultName << "' found.\n";
        cout << "  Use the Password Vault option to create one first.\n";
        resetColor();
        cout << "\n  Press Enter to continue...";
        cin.ignore(1000, '\n');
        return;
    }

    // Attempt to open with up to 3 password tries
    PasswordVault vault;
    for (int attempt = 1; attempt <= 3; attempt++) {
        if (vault.isVaultLocked()) {
            while (true) {
                int remaining = vault.getLockRemainingTime();
                if (remaining <= 0) break;
                setColor(12);
                cout << "\r  Vault locked. Please wait " << remaining << " second(s)...   ";
                resetColor();
                cout.flush();
                time_t start = time(0);
                while (difftime(time(0), start) < 1.0) {}
            }
            setColor(14);
            cout << "\n\n  Lockout expired. You may try again.\n\n";
            resetColor();
            attempt = 1;
        }

        string masterPwd;
        setColor(8);
        cout << "  Enter master password (attempt " << attempt << "/3): ";
        resetColor();
        cin >> masterPwd;
        cin.ignore(1000, '\n');

        if (vault.open(vaultName, masterPwd)) {
            setColor(10);
            cout << "\n  Vault '" << vaultName << "' opened. Running health scan...\n";
            resetColor();
            Sleep(500);
            break;
        }

        if (vault.isVaultLocked()) continue;

        int left = 3 - attempt;
        setColor(12);
        if (left > 0)
            cout << "  Wrong password. " << left << " attempt(s) remaining.\n";
        resetColor();
    }

    if (!vault.getIsOpen()) {
        setColor(12);
        cout << "\n  Could not open vault. Returning to menu.\n";
        resetColor();
        cout << "\n  Press Enter to continue...";
        cin.ignore(1000, '\n');
        return;
    }

    LeakChecker       lc("leaked_passwords.txt");
    PasswordEvaluator pe;
    HealthDashboard   hd;

    hd.analyzeVault(vault, lc, pe);
    hd.displaySummary();

    cout << "  Press Enter to continue...";
    cin.ignore(1000, '\n');
}

// ═════════════════════════════════════════════════════════════════════════════
//  MAIN MENU
// ═════════════════════════════════════════════════════════════════════════════
void showMenu() {
    system("cls");
    setColor(11);
    cout << "\n  ==========================================\n";
    cout << "       PASSWORD SECURITY SUITE v1.0\n";
    cout << "  ==========================================\n";
    resetColor();

    setColor(8);
    cout << "   Your personal password security toolkit\n\n";
    resetColor();

    setColor(14); cout << "   [1]"; resetColor(); cout << "  Evaluate a Password\n";
    setColor(14); cout << "   [2]"; resetColor(); cout << "  Generate a Password\n";
    setColor(14); cout << "   [3]"; resetColor(); cout << "  Password Vault\n";
    setColor(14); cout << "   [4]"; resetColor(); cout << "  Check Password Leak\n";
    setColor(14); cout << "   [5]"; resetColor(); cout << "  Vault Health Dashboard\n";

    cout << "\n";
    setColor(12); cout << "   [0]"; resetColor(); cout << "  Exit\n";

    setColor(11);
    cout << "\n  ==========================================\n";
    resetColor();
}

// ═════════════════════════════════════════════════════════════════════════════
//  ENTRY POINT
// ═════════════════════════════════════════════════════════════════════════════
int main() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode);

    string input = "";
    int choice   = -1;

    while (true) {
        showMenu();

        setColor(8);
        cout << "   Enter your choice: ";
        resetColor();

        cin >> input;
        cin.ignore(1000, '\n');

        bool valid = (input.length() == 1 && isdigit(input[0]));
        if (!valid) {
            setColor(12);
            cout << "\n  Invalid input. Please enter a number from the menu.\n";
            resetColor();
            cout << "  Press Enter to continue...";
            cin.ignore(1000, '\n');
            continue;
        }

        choice = stoi(input);

        if (choice == 0) {
            setColor(10);
            cout << "\n  Goodbye! Stay secure.\n\n";
            resetColor();
            break;
        }

        switch (choice) {
            case 1: runPasswordEvaluator(); break;
            case 2: runGeneratorMenu();     break;
            case 3: runVaultMenu();         break;
            case 4: runLeakChecker();       break;
            case 5: runHealthDashboard();   break;
            default:
                setColor(12);
                cout << "\n  Invalid choice.\n";
                resetColor();
                cout << "  Press Enter to continue...";
                cin.ignore(1000, '\n');
                break;
        }
    }

    return 0;
}