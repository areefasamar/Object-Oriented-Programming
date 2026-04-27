#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ============================================================
// 1. COMPONENT: LearningComponent (Abstract Base Class)
// ============================================================
class LearningComponent {
public:
    virtual void start() = 0;
    virtual bool isCompleted() = 0;
    virtual int getTotalXP() = 0;
    virtual string getTitle() = 0;
    virtual ~LearningComponent() {}
};

// ============================================================
// 2. LEAF: Exercise (The smallest unit)
// ============================================================
class Exercise : public LearningComponent {
private:
    string title;
    int xpValue;
    bool completed;

public:
    Exercise(string t, int xp) : title(t), xpValue(xp), completed(false) {}

    void start() override {
        cout << "      [Exercise] Starting: " << title << "..." << endl;
        completed = true; // Simulating completion
    }

    bool isCompleted() override { return completed; }
    int getTotalXP() override { return xpValue; }
    string getTitle() override { return title; }
};

// ============================================================
// 3. COMPOSITE: Base Container (Common logic for Course, Unit, etc.)
// ============================================================
class LearningContainer : public LearningComponent {
protected:
    string title;
    vector<LearningComponent*> children;

public:
    LearningContainer(string t) : title(t) {}

    void add(LearningComponent* component) {
        children.push_back(component);
    }

    string getTitle() override { return title; }

    // Start runs all children recursively
    void start() override {
        cout << "\n>>> Entering " << title << "..." << endl;
        for (auto child : children) {
            child->start();
        }
    }

    // Returns true only if ALL children are completed
    bool isCompleted() override {
        for (auto child : children) {
            if (!child->isCompleted()) return false;
        }
        return true;
    }

    // Sums up XP from all children all the way down
    int getTotalXP() override {
        int total = 0;
        for (auto child : children) {
            total += child->getTotalXP();
        }
        return total;
    }

    ~LearningContainer() {
        for (auto child : children) delete child;
    }
};

// --- Specific Composite Types (Hierarchy Levels) ---

class Lesson : public LearningContainer {
public:
    Lesson(string t) : LearningContainer(t) {}
};

class Unit : public LearningContainer {
public:
    Unit(string t) : LearningContainer(t) {}
};

class Section : public LearningContainer {
public:
    Section(string t) : LearningContainer(t) {}
};

class Course : public LearningContainer {
public:
    Course(string t) : LearningContainer(t) {}
};

// ============================================================
// 4. MAIN - Building the Duolingo Tree
// ============================================================
int main() {
    // A. Create Exercises (Leaves)
    Exercise* ex1 = new Exercise("Translate 'Hello'", 10);
    Exercise* ex2 = new Exercise("Match 'Adios'", 5);
    Exercise* ex3 = new Exercise("Speaking: 'Buenos dias'", 15);

    // B. Group into a Lesson (Composite)
    Lesson* lesson1 = new Lesson("Lesson 1: Greetings");
    lesson1->add(ex1);
    lesson1->add(ex2);

    // C. Group Lesson into a Unit
    Unit* unit1 = new Unit("Unit 1: The Basics");
    unit1->add(lesson1);
    
    // Adding another direct exercise to Unit (just to show flexibility)
    unit1->add(ex3);

    // D. Group Unit into a Section
    Section* section1 = new Section("Section: Intro to Spanish");
    section1->add(unit1);

    // E. Root: The Course
    Course* myCourse = new Course("Spanish for English Speakers");
    myCourse->add(section1);

    // --- EXECUTION ---
    cout << "COURSE TITLE: " << myCourse->getTitle() << endl;
    
    // Client doesn't care if it's a course or an exercise
    myCourse->start();

    cout << "\n--- FINAL STATS ---" << endl;
    cout << "Total Course XP: " << myCourse->getTotalXP() << " XP" << endl;
    cout << "Course Status: " << (myCourse->isCompleted() ? "Completed! ?" : "In Progress... ?") << endl;

    delete myCourse; // Deletes the entire tree
    return 0;
}