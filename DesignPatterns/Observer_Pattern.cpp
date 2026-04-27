#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ============================================================
// 1. THE OBSERVER INTERFACE
// ============================================================
class LessonObserver {
public:
    virtual void onLessonCompleted(string username, int xpEarned, bool perfectLesson) = 0;
    virtual ~LessonObserver() {}
};

// ============================================================
// 2. CONCRETE OBSERVERS (Real Duolingo Systems)
// ============================================================

// System 1: Streak Management
class StreakObserver : public LessonObserver {
public:
    void onLessonCompleted(string username, int xpEarned, bool perfectLesson) override {
        cout << "[STREAK] Checking timestamp... 24h since last lesson? Yes!" << endl;
        cout << "   >> Flame icon is glowing! Your streak is now 45 days." << endl;
    }
};

// System 2: League & Leaderboard (XP)
class LeagueObserver : public LessonObserver {
public:
    void onLessonCompleted(string username, int xpEarned, bool perfectLesson) override {
        int bonus = perfectLesson ? 5 : 0; // Combo bonus
        cout << "[LEAGUE] Added " << xpEarned + bonus << " XP to your Bronze League score." << endl;
        cout << "   >> You moved up to 4th place! (Perfect Lesson Bonus: +" << bonus << " XP)" << endl;
    }
};

// System 3: Health & Hearts (If they finish, maybe refill?)
class HealthObserver : public LessonObserver {
public:
    void onLessonCompleted(string username, int xpEarned, bool perfectLesson) override {
        if (perfectLesson) {
            cout << "[HEALTH] Perfect lesson! You earned back 1 Heart <3" << endl;
        } else {
            cout << "[HEALTH] Lesson finished. Health remains stable." << endl;
        }
    }
};

// System 4: Inventory & Gems (Lingots)
class GemObserver : public LessonObserver {
public:
    void onLessonCompleted(string username, int xpEarned, bool perfectLesson) override {
        cout << "[GEMS] Lesson rewards: +12 Gems added to your account." << endl;
    }
};

// System 5: Daily Quests Tracking
class QuestObserver : public LessonObserver {
public:
    void onLessonCompleted(string username, int xpEarned, bool perfectLesson) override {
        cout << "[QUESTS] Progress: 'Finish 1 Lesson' [1/1] - COMPLETED!" << endl;
        cout << "   >> Progress: 'Earn 50 XP' [20/50] - In Progress..." << endl;
    }
};

// ============================================================
// 3. THE SUBJECT (LessonController)
// ============================================================
class LessonController {
private:
    vector<LessonObserver*> observers;

public:
    void subscribe(LessonObserver* obs) {
        observers.push_back(obs);
    }

    void unsubscribe(LessonObserver* obs) {
        for (auto it = observers.begin(); it != observers.end(); ++it) {
            if (*it == obs) {
                observers.erase(it);
                break;
            }
        }
    }

    // Trigger the event
    void finishLesson(string username, int xp, bool perfect) {
        cout << "\n==========================================" << endl;
        cout << "   LESSON SUMMARY FOR: " << username << endl;
        cout << "==========================================" << endl;
        
        for (auto obs : observers) {
            obs->onLessonCompleted(username, xp, perfect);
        }
    }
};

// ============================================================
// 4. MAIN - Running the Duo engine
// ============================================================
int main() {
    LessonController duoEngine;

    // Create real systems
    StreakObserver streak;
    LeagueObserver league;
    HealthObserver health;
    GemObserver gems;
    QuestObserver quests;

    // Registering the systems
    duoEngine.subscribe(&streak);
    duoEngine.subscribe(&league);
    duoEngine.subscribe(&health);
    duoEngine.subscribe(&gems);
    duoEngine.subscribe(&quests);

    // Scenario A: Humaira finishes a lesson perfectly
    duoEngine.finishLesson("Humaira", 15, true);

    // Scenario B: User disables Gem notifications (Inventory updates)
    cout << "\n[System] User muted shop notifications..." << endl;
    duoEngine.unsubscribe(&gems);

    // Scenario C: Another lesson finished (Gems system won't fire)
    duoEngine.finishLesson("Humaira", 10, false);

    return 0;
}