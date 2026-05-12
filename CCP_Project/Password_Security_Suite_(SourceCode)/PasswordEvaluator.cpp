#include "PasswordEvaluator.h"
#include "WinCompat.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
using namespace std;

// ── Colour helpers ─────────────────────────────────────────────────────────
static void evalSetColor(int code) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), code);
}
static void evalResetColor() { evalSetColor(7); }


// ─────────────────────────────────────────────
//  CONSTRUCTOR
// ─────────────────────────────────────────────
PasswordEvaluator::PasswordEvaluator()
    : password(""), score(0), level(VERY_WEAK) {}


// ─────────────────────────────────────────────
//  SETTER
// ─────────────────────────────────────────────
void PasswordEvaluator::setPassword(const string& pwd) {
    if (pwd.empty()) {
        throw invalid_argument("Password cannot be empty.");
    }
    if (pwd.length() > 128) {
        throw invalid_argument("Password is too long (max 128 characters).");
    }
    for (char c : pwd) {
        if (c == ' ') {
            throw invalid_argument("Password should not contain spaces.");
        }
    }
    password = pwd;
    score    = 0;
    level    = VERY_WEAK;
}


// ─────────────────────────────────────────────
//  PRIVATE CHECKERS
// ─────────────────────────────────────────────

bool PasswordEvaluator::checkLength() const {
    return password.length() >= 8;
}

bool PasswordEvaluator::checkUppercase() const {
    for (char c : password) {
        if (isupper(c)) return true;
    }
    return false;
}

bool PasswordEvaluator::checkDigits() const {
    for (char c : password) {
        if (isdigit(c)) return true;
    }
    return false;
}

bool PasswordEvaluator::checkSymbols() const {
    string symbols = "@#$!%&*-_+=?";
    for (char c : password) {
        if (symbols.find(c) != string::npos) return true;
    }
    return false;
}

bool PasswordEvaluator::checkCommonPatterns() const {
    string patterns[] = {
        "123", "1234", "12345", "123456",
        "abc", "abcd", "abcde",
        "qwerty", "qwert", "asdf",
        "password", "pass", "1111", "0000",
        "aaa", "aaaa", "admin", "login",
        "letmein", "welcome", "monkey", "dragon"
    };
    int patternCount = 22;

    string lower = "";
    for (char c : password) {
        lower += tolower(c);
    }

    for (int i = 0; i < patternCount; i++) {
        if (lower.find(patterns[i]) != string::npos) {
            return true;
        }
    }
    return false;
}

bool PasswordEvaluator::checkLeakedList() const {
    ifstream file("leaked_passwords.txt");
    if (!file.is_open()) {
        return false;
    }

    string line;
    string lower = "";
    for (char c : password) lower += tolower(c);

    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        string lineLower = "";
        for (char c : line) lineLower += tolower(c);

        if (lineLower == lower) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}


// ─────────────────────────────────────────────
//  SCORE CALCULATOR
// ─────────────────────────────────────────────
void PasswordEvaluator::calculateScore() {
    score = 0;

    int len = password.length();
    if      (len >= 20) score += 30;
    else if (len >= 16) score += 25;
    else if (len >= 12) score += 20;
    else if (len >= 8 ) score += 12;
    else                score += 5;

    if (checkUppercase()) score += 15;
    if (checkDigits())    score += 15;
    if (checkSymbols())   score += 20;

    bool hasLower = false;
    for (char c : password) {
        if (islower(c)) { hasLower = true; break; }
    }
    if (hasLower) score += 10;

    if (checkCommonPatterns()) score -= 20;
    if (checkLeakedList())     score  = 0;

    if (score < 0)   score = 0;
    if (score > 100) score = 100;

    if      (score >= 80) level = VERY_STRONG;
    else if (score >= 60) level = STRONG;
    else if (score >= 40) level = MODERATE;
    else if (score >= 20) level = WEAK;
    else                  level = VERY_WEAK;
}


// ─────────────────────────────────────────────
//  CRACK TIME ESTIMATOR
// ─────────────────────────────────────────────
string PasswordEvaluator::getCrackTime() const {
    if      (score >= 80) return "Centuries (practically uncrackable)";
    else if (score >= 60) return "Several years";
    else if (score >= 40) return "A few hours to days";
    else if (score >= 20) return "A few minutes";
    else                  return "Less than 1 second";
}


// ─────────────────────────────────────────────
//  PUBLIC EVALUATE
// ─────────────────────────────────────────────
void PasswordEvaluator::evaluate() {
    if (password.empty()) {
        throw runtime_error("No password set. Call setPassword() first.");
    }
    calculateScore();
}


// ─────────────────────────────────────────────
//  DISPLAY REPORT
// ─────────────────────────────────────────────
void PasswordEvaluator::displayReport() const {

    cout << "\n";
    evalSetColor(11);
    cout << "  ========================================\n";
    cout << "         PASSWORD STRENGTH REPORT\n";
    cout << "  ========================================\n";
    evalResetColor();

    evalSetColor(8);  cout << "  Password  : "; evalResetColor();
    cout << password << "\n";

    evalSetColor(8);  cout << "  Score     : "; evalResetColor();
    // Color the score based on value
    if      (score >= 80) evalSetColor(10);
    else if (score >= 60) evalSetColor(14);
    else if (score >= 40) evalSetColor(14);
    else                  evalSetColor(12);
    cout << score << " / 100";
    evalResetColor();
    cout << "\n";

    // Visual bar
    evalSetColor(8); cout << "  Strength  : "; evalResetColor();
    cout << "[";
    int filled = score / 5;
    for (int i = 0; i < 20; i++) {
        if (i < filled) {
            if      (score >= 80) evalSetColor(10);
            else if (score >= 40) evalSetColor(14);
            else                  evalSetColor(12);
            cout << "#";
            evalResetColor();
        } else {
            evalSetColor(8); cout << "-"; evalResetColor();
        }
    }
    cout << "] ";

    if      (level == VERY_STRONG) { evalSetColor(10); cout << "VERY STRONG\n"; }
    else if (level == STRONG)      { evalSetColor(10); cout << "STRONG\n";      }
    else if (level == MODERATE)    { evalSetColor(14); cout << "MODERATE\n";    }
    else if (level == WEAK)        { evalSetColor(12); cout << "WEAK\n";        }
    else                           { evalSetColor(12); cout << "VERY WEAK\n";   }
    evalResetColor();

    evalSetColor(8); cout << "  Crack Time: "; evalResetColor();
    if      (score >= 80) evalSetColor(10);
    else if (score >= 40) evalSetColor(14);
    else                  evalSetColor(12);
    cout << getCrackTime() << "\n";
    evalResetColor();

    evalSetColor(11);
    cout << "\n  ---- Criteria Breakdown ----\n";
    evalResetColor();

    // Helper lambda-style macro — we use inline ternary + color
    auto printCriteria = [](bool passed, const string& msg) {
        if (passed) { evalSetColor(10); cout << "  [PASS] "; }
        else        { evalSetColor(12); cout << "  [FAIL] "; }
        evalResetColor();
        cout << msg << "\n";
    };

    printCriteria(checkLength(),          "Length is 8 or more characters");
    printCriteria(checkUppercase(),       "Contains uppercase letters (A-Z)");
    printCriteria(checkDigits(),          "Contains numbers (0-9)");
    printCriteria(checkSymbols(),         "Contains symbols (@#$!...)");
    printCriteria(!checkCommonPatterns(), "No common weak patterns (123, abc, qwerty)");
    printCriteria(!checkLeakedList(),     "Not found in known leaked passwords list");

    evalSetColor(11);
    cout << "\n  ---- Suggestions ----\n";
    evalResetColor();

    bool allGood = true;

    if (!checkLength()) {
        evalSetColor(14); cout << "  -> "; evalResetColor();
        cout << "Make your password at least 8 characters long.\n";
        allGood = false;
    }
    if (!checkUppercase()) {
        evalSetColor(14); cout << "  -> "; evalResetColor();
        cout << "Add at least one uppercase letter (e.g. A, B, C).\n";
        allGood = false;
    }
    if (!checkDigits()) {
        evalSetColor(14); cout << "  -> "; evalResetColor();
        cout << "Add at least one number (e.g. 3, 7, 9).\n";
        allGood = false;
    }
    if (!checkSymbols()) {
        evalSetColor(14); cout << "  -> "; evalResetColor();
        cout << "Add a symbol like @, #, $, or ! to boost strength.\n";
        allGood = false;
    }
    if (checkCommonPatterns()) {
        evalSetColor(12); cout << "  -> "; evalResetColor();
        cout << "Remove common patterns like '123', 'abc', or 'qwerty'.\n";
        allGood = false;
    }
    if (checkLeakedList()) {
        evalSetColor(12); cout << "  -> "; evalResetColor();
        cout << "This password was found in a known data breach list!\n";
        evalSetColor(12); cout << "  -> "; evalResetColor();
        cout << "You must NOT use this password anywhere.\n";
        allGood = false;
    }
    if (password.length() < 12 && level != VERY_STRONG) {
        evalSetColor(14); cout << "  -> "; evalResetColor();
        cout << "Consider making it 12+ characters for better protection.\n";
        allGood = false;
    }

    if (allGood) {
        evalSetColor(10);
        cout << "  Great job! Your password meets all the criteria.\n";
        evalResetColor();
    }

    evalSetColor(11);
    cout << "  ========================================\n\n";
    evalResetColor();
}


// ─────────────────────────────────────────────
//  GETTERS
// ─────────────────────────────────────────────
int           PasswordEvaluator::getScore()    const { return score;    }
StrengthLevel PasswordEvaluator::getLevel()    const { return level;    }
string        PasswordEvaluator::getPassword() const { return password; }
