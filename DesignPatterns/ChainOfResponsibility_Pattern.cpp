#include <iostream>
#include <string>
using namespace std;

// ============================================================
// 1. HANDLER (Abstract Base Class)
// ============================================================
class Validator {
protected:
    Validator* next;  // next handler in the chain

public:
    Validator() : next(NULL) {}

    void setNext(Validator* n) { next = n; }

    // Returns true if accepted, false if rejected
    virtual bool validate(string userAnswer, string correctAnswer) = 0;

    virtual ~Validator() {}
};

// ============================================================
// 2. CONCRETE HANDLERS (Duolingo-like validators)
// ============================================================

// A) Empty Check
class EmptyCheck : public Validator {
public:
    bool validate(string userAnswer, string correctAnswer) override {
        if (userAnswer == "") {
            cout << "[EmptyCheck] Rejected: Answer is empty.\n";
            return false; // stop chain
        }
        // pass to next
        if (next != NULL) return next->validate(userAnswer, correctAnswer);
        return false;
    }
};

// B) Minimum Length Check
class MinLengthCheck : public Validator {
private:
    int minLen;

public:
    MinLengthCheck(int m) : minLen(m) {}

    bool validate(string userAnswer, string correctAnswer) override {
        if ((int)userAnswer.size() < minLen) {
            cout << "[MinLengthCheck] Rejected: Too short.\n";
            return false; // stop chain
        }
        if (next != NULL) return next->validate(userAnswer, correctAnswer);
        return false;
    }
};

// C) Typo Tolerance (very simple: allow 1 character difference in length)
class TypoCheck : public Validator {
public:
    bool validate(string userAnswer, string correctAnswer) override {
        int diff = (int)userAnswer.size() - (int)correctAnswer.size();
        if (diff < 0) diff = -diff;

        if (userAnswer != correctAnswer && diff <= 1) {
            cout << "[TypoCheck] Accepted with warning: Minor typo (partial accept).\n";
            return true; // stop chain (accept here)
        }
        if (next != NULL) return next->validate(userAnswer, correctAnswer);
        return false;
    }
};

// D) Strict Correctness Check (final decision)
class StrictCheck : public Validator {
public:
    bool validate(string userAnswer, string correctAnswer) override {
        if (userAnswer == correctAnswer) {
            cout << "[StrictCheck] Accepted: Exact match!\n";
            return true;
        }
        cout << "[StrictCheck] Rejected: Incorrect answer.\n";
        return false; // final handler decides
    }
};

// ============================================================
// 3. MAIN (Build the chain and test)
// ============================================================
int main() {
    // Create validators
    EmptyCheck empty;
    MinLengthCheck minLen(2);
    TypoCheck typo;
    StrictCheck strict;

    // Build chain: Empty -> MinLength -> Typo -> Strict
    empty.setNext(&minLen);
    minLen.setNext(&typo);
    typo.setNext(&strict);

    cout << "=== Duolingo Answer Validation (Chain of Responsibility) ===\n\n";

    // Test cases
    cout << "Case 1: Empty answer\n";
    empty.validate("", "hello");

    cout << "\nCase 2: Too short\n";
    empty.validate("h", "hello");

    cout << "\nCase 3: Minor typo (length diff <= 1)\n";
    empty.validate("hell", "hello");

    cout << "\nCase 4: Correct answer\n";
    empty.validate("hello", "hello");

    cout << "\nCase 5: Incorrect answer\n";
    empty.validate("world", "hello");

    return 0;
}
