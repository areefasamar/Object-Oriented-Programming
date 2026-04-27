#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// ============================================================
// A) OBSERVER PATTERN - Lesson completion event subscribers
// ============================================================
class LessonObserver {
public:
    virtual void onLessonCompleted(const string& username, int xpEarned, bool perfectLesson) = 0;
    virtual ~LessonObserver() = default;
};

class StreakObserver : public LessonObserver {
public:
    void onLessonCompleted(const string& username, int xpEarned, bool perfectLesson) override {
        (void)username; (void)xpEarned; (void)perfectLesson;
        cout << "[STREAK] Checking timestamp... 24h since last lesson? Yes!\n"
             << "   >> Flame icon is glowing! Your streak is now 45 days.\n";
    }
};

class LeagueObserver : public LessonObserver {
public:
    void onLessonCompleted(const string& username, int xpEarned, bool perfectLesson) override {
        (void)username;
        int bonus = perfectLesson ? 5 : 0;
        cout << "[LEAGUE] Added " << (xpEarned + bonus) << " XP to your Bronze League score.\n"
             << "   >> You moved up to 4th place! (Perfect Lesson Bonus: +" << bonus << " XP)\n";
    }
};

class HealthObserver : public LessonObserver {
public:
    void onLessonCompleted(const string& username, int xpEarned, bool perfectLesson) override {
        (void)username; (void)xpEarned;
        if (perfectLesson) cout << "[HEALTH] Perfect lesson! You earned back 1 Heart <3\n";
        else cout << "[HEALTH] Lesson finished. Health remains stable.\n";
    }
};

class GemObserver : public LessonObserver {
public:
    void onLessonCompleted(const string& username, int xpEarned, bool perfectLesson) override {
        (void)username; (void)xpEarned; (void)perfectLesson;
        cout << "[GEMS] Lesson rewards: +12 Gems added to your account.\n";
    }
};

class QuestObserver : public LessonObserver {
public:
    void onLessonCompleted(const string& username, int xpEarned, bool perfectLesson) override {
        (void)username; (void)xpEarned; (void)perfectLesson;
        cout << "[QUESTS] Progress: 'Finish 1 Lesson' [1/1] - COMPLETED!\n"
             << "   >> Progress: 'Earn 50 XP' [20/50] - In Progress...\n";
    }
};

// ============================================================
// B) CHAIN OF RESPONSIBILITY - Validators for answers
// ============================================================
class Validator {
protected:
    Validator* next = nullptr;

public:
    virtual ~Validator() = default;

    void setNext(Validator* n) { next = n; }

    // true => accepted, false => rejected
    virtual bool validate(const string& userAnswer, const string& correctAnswer) = 0;

protected:
    bool passToNext(const string& userAnswer, const string& correctAnswer) {
        if (next) return next->validate(userAnswer, correctAnswer);
        return false;
    }
};

class EmptyCheck : public Validator {
public:
    bool validate(const string& userAnswer, const string& correctAnswer) override {
        (void)correctAnswer;
        if (userAnswer.empty()) {
            cout << "      [EmptyCheck] Rejected: Answer is empty.\n";
            return false;
        }
        return passToNext(userAnswer, correctAnswer);
    }
};

class MinLengthCheck : public Validator {
private:
    int minLen;

public:
    explicit MinLengthCheck(int m) : minLen(m) {}

    bool validate(const string& userAnswer, const string& correctAnswer) override {
        (void)correctAnswer;
        if ((int)userAnswer.size() < minLen) {
            cout << "      [MinLengthCheck] Rejected: Too short.\n";
            return false;
        }
        return passToNext(userAnswer, correctAnswer);
    }
};

class TypoCheck : public Validator {
public:
    bool validate(const string& userAnswer, const string& correctAnswer) override {
        int diff = (int)userAnswer.size() - (int)correctAnswer.size();
        diff = std::abs(diff);

        if (userAnswer != correctAnswer && diff <= 1) {
            cout << "      [TypoCheck] Accepted with warning: Minor typo (partial accept).\n";
            return true; // accept early
        }
        return passToNext(userAnswer, correctAnswer);
    }
};

class StrictCheck : public Validator {
public:
    bool validate(const string& userAnswer, const string& correctAnswer) override {
        if (userAnswer == correctAnswer) {
            cout << "      [StrictCheck] Accepted: Exact match!\n";
            return true;
        }
        cout << "      [StrictCheck] Rejected: Incorrect answer.\n";
        return false;
    }
};

// Small helper to own/build the chain neatly (avoids memory leaks).
class ValidationChain {
private:
    EmptyCheck empty;
    MinLengthCheck minLen;
    TypoCheck typo;
    StrictCheck strict;

public:
    explicit ValidationChain(int minLength)
        : minLen(minLength) {
        empty.setNext(&minLen);
        minLen.setNext(&typo);
        typo.setNext(&strict);
    }

    bool validate(const string& userAnswer, const string& correctAnswer) {
        return empty.validate(userAnswer, correctAnswer);
    }
};

// ============================================================
// C) COMPOSITE PATTERN - Learning tree (Course/Section/Unit/Lesson/Exercise)
// ============================================================
class LessonController; // forward

class LearningComponent {
public:
    virtual void start(const string& username) = 0;
    virtual bool isCompleted() const = 0;
    virtual int getTotalXP() const = 0;
    virtual string getTitle() const = 0;
    virtual ~LearningComponent() = default;
};

// Leaf
class Exercise : public LearningComponent {
private:
    string title;
    int xpValue;
    bool completed = false;

    // For demo purposes
    string correctAnswer;
    string simulatedUserAnswer;

    ValidationChain chain;

public:
    Exercise(string t, int xp, string correct, string userSimulated, int minLen = 2)
        : title(std::move(t)),
          xpValue(xp),
          correctAnswer(std::move(correct)),
          simulatedUserAnswer(std::move(userSimulated)),
          chain(minLen) {}

    void start(const string& username) override {
        (void)username;
        cout << "      [Exercise] " << title << "\n";
        cout << "         Prompt: (correct = \"" << correctAnswer << "\")\n";
        cout << "         User answered: \"" << simulatedUserAnswer << "\"\n";

        bool ok = chain.validate(simulatedUserAnswer, correctAnswer);
        completed = ok;

        if (completed) {
            cout << "      -> Exercise completed! +" << xpValue << " XP\n";
        } else {
            cout << "      -> Exercise failed. +0 XP\n";
        }
    }

    bool isCompleted() const override { return completed; }
    int getTotalXP() const override { return completed ? xpValue : 0; }
    string getTitle() const override { return title; }
};

// Composite base
class LearningContainer : public LearningComponent {
protected:
    string title;
    vector<LearningComponent*> children; // owned

public:
    explicit LearningContainer(string t) : title(std::move(t)) {}

    void add(LearningComponent* component) { children.push_back(component); }

    string getTitle() const override { return title; }

    void start(const string& username) override {
        cout << "\n>>> Entering " << title << "...\n";
        for (auto child : children) child->start(username);
    }

    bool isCompleted() const override {
        for (auto child : children) {
            if (!child->isCompleted()) return false;
        }
        return true;
    }

    int getTotalXP() const override {
        int total = 0;
        for (auto child : children) total += child->getTotalXP();
        return total;
    }

    virtual ~LearningContainer() {
        for (auto child : children) delete child;
    }
};

// A Lesson is a composite, but also a place where observers fire when completed.
class Lesson : public LearningContainer {
private:
    LessonController* controller; // not owned

public:
    Lesson(string t, LessonController* c) : LearningContainer(std::move(t)), controller(c) {}
    void start(const string& username) override; // defined after LessonController
};

class Unit : public LearningContainer {
public:
    explicit Unit(string t) : LearningContainer(std::move(t)) {}
};

class Section : public LearningContainer {
public:
    explicit Section(string t) : LearningContainer(std::move(t)) {}
};

class Course : public LearningContainer {
public:
    explicit Course(string t) : LearningContainer(std::move(t)) {}
};

// ============================================================
// D) SUBJECT - LessonController (ties observer notifications to lesson completion)
// ============================================================
class LessonController {
private:
    vector<LessonObserver*> observers; // not owned

public:
    void subscribe(LessonObserver* obs) { observers.push_back(obs); }

    void unsubscribe(LessonObserver* obs) {
        for (auto it = observers.begin(); it != observers.end(); ++it) {
            if (*it == obs) {
                observers.erase(it);
                break;
            }
        }
    }

    void finishLesson(const string& username, const string& lessonTitle, int xpEarned, bool perfect) {
        cout << "\n==========================================\n";
        cout << "   LESSON SUMMARY FOR: " << username << "\n";
        cout << "   LESSON: " << lessonTitle << "\n";
        cout << "   XP EARNED: " << xpEarned << "\n";
        cout << "   PERFECT: " << (perfect ? "YES" : "NO") << "\n";
        cout << "==========================================\n";

        for (auto obs : observers) {
            obs->onLessonCompleted(username, xpEarned, perfect);
        }
    }
};

void Lesson::start(const string& username) {
    cout << "\n>>> Entering " << title << "...\n";
    for (auto child : children) child->start(username);

    int xp = getTotalXP();
    bool perfect = isCompleted(); // perfect means all exercises accepted
    if (controller) controller->finishLesson(username, title, xp, perfect);
}

// ============================================================
// E) MAIN - Demo run
// ============================================================
int main() {
    LessonController duoEngine;

    // Observers (systems)
    StreakObserver streak;
    LeagueObserver league;
    HealthObserver health;
    GemObserver gems;
    QuestObserver quests;

    duoEngine.subscribe(&streak);
    duoEngine.subscribe(&league);
    duoEngine.subscribe(&health);
    duoEngine.subscribe(&gems);
    duoEngine.subscribe(&quests);

    // Build a composite learning tree:
    // Course -> Section -> Unit -> Lesson -> Exercises
    Course* myCourse = new Course("Spanish for English Speakers");
    Section* section1 = new Section("Section: Intro to Spanish");
    Unit* unit1 = new Unit("Unit 1: The Basics");

    Lesson* lesson1 = new Lesson("Lesson 1: Greetings", &duoEngine);
    lesson1->add(new Exercise("Translate 'Hello'", 10, "hello", "hello")); // correct
    lesson1->add(new Exercise("Match 'Adios'", 5, "adios", "adi"));        // typo accept (len diff 2? actually 5 vs 3 diff 2 => will go strict and fail)
    // Let's make it a minor typo (diff <= 1) so it demonstrates TypoCheck:
    lesson1->add(new Exercise("Speaking: 'Buenos dias'", 15, "buenos", "bueno")); // diff 1 => TypoCheck accepts

    unit1->add(lesson1);

    // Add another lesson to show multiple lesson events
    Lesson* lesson2 = new Lesson("Lesson 2: Basics", &duoEngine);
    lesson2->add(new Exercise("Type 'yes'", 5, "si", ""));      // empty => fail
    lesson2->add(new Exercise("Type 'no'", 5, "no", "n"));      // too short => fail
    unit1->add(lesson2);

    section1->add(unit1);
    myCourse->add(section1);

    // Run scenario A
    cout << "COURSE TITLE: " << myCourse->getTitle() << "\n";
    myCourse->start("Humaira");

    // User mutes gem notifications, then replays lesson 1 by starting it again (demo)
    cout << "\n[System] User muted shop notifications...\n";
    duoEngine.unsubscribe(&gems);

    cout << "\n[Replay] Re-running Lesson 1 only...\n";
    lesson1->start("Humaira");

    cout << "\n--- COURSE STATS (current run state) ---\n";
    cout << "Total Course XP (sum of completed exercises): " << myCourse->getTotalXP() << " XP\n";
    cout << "Course Status: " << (myCourse->isCompleted() ? "Completed!" : "In Progress...") << "\n";

    delete myCourse; // deletes entire composite tree
    return 0;
}