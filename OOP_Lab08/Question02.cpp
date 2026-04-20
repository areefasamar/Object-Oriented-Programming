#include <iostream>
#include <string>
using namespace std;

class Character {
    protected:
        string name;
        int level;
        int health;

    public:
        Character(string n, int l, int h): name(n), level(l), health(h) {}

        string getName(){ 
            return name; 
        }
        
        int getLevel(){ 
            return level; 
        }
        
        int getHealth(){ 
            return health; 
        }
};

class Warrior : virtual public Character {
    protected:
        int strength;
        string meleeWeaponsProficiency;

    public:
        Warrior(string n, int l, int h, int str, string meleeProf)
            : Character(n, l, h), strength(str), meleeWeaponsProficiency(meleeProf) {}

        int getStrength(){ 
            return strength; 
        }
        
        string getMeleeWeaponsProficiency(){ 
            return meleeWeaponsProficiency; 
        }

        void slash(){
            cout << name << " performs a powerful slash attack!" << endl;
        }
};

class Mage : virtual public Character {
    protected:
        int intelligence;
        string spellCastingProficiency;

    public:
        Mage(string n, int l, int h, int intel, string spellProf)
            : Character(n, l, h), intelligence(intel), spellCastingProficiency(spellProf) {}

        int getIntelligence(){ 
            return intelligence; 
        }
        
        string getSpellCastingProficiency(){ 
            return spellCastingProficiency; 
        }

        void fireball(){
            cout << name << " casts a blazing fireball!" << endl;
        }
};

class Archer : virtual public Character {
    protected:
        int dexterity;
        string rangedWeaponsProficiency;

    public:
        Archer(string n, int l, int h, int dex, string rangedProf)
            : Character(n, l, h), dexterity(dex), rangedWeaponsProficiency(rangedProf) {}

        int getDexterity(){ 
            return dexterity; 
        }
        
        string getRangedWeaponsProficiency(){ 
            return rangedWeaponsProficiency; 
        }

        void rapidShot(){
            cout << name << " fires a rapid shot!" << endl;
        }
};

class NPC : virtual public Character {
    protected:
        string movementPattern;
        string scriptedDialogue;

    public:
        NPC(string n, int l, int h, string movement, string dialogue)
            : Character(n, l, h), movementPattern(movement), scriptedDialogue(dialogue) {}

        string getMovementPattern(){ 
            return movementPattern; 
        }
        
        string getScriptedDialogue(){ 
            return scriptedDialogue; 
        }
        
        void speak(){
            cout << name << " says: \"" << scriptedDialogue << "\"" << endl;
        }
};

class Mighty : public Warrior, public Mage {
    public:
        Mighty(string n, int l, int h, int str, string meleeProf, int intel, string spellProf)
            : Character(n, l, h), 
              Warrior(n, l, h, str, meleeProf), 
              Mage(n, l, h, intel, spellProf) {}

        void displayMightyStats(){
            cout << "==== Mighty Character Stats ====" << endl;
            cout << "Name: " << name << endl;
            cout << "Level: " << level << endl;
            cout << "Health: " << health << endl;
            cout << "Strength: " << strength << endl;
            cout << "Melee Proficiency: " << meleeWeaponsProficiency << endl;
            cout << "Intelligence: " << intelligence << endl;
            cout << "Spell Proficiency: " << spellCastingProficiency << endl;
            cout << "================================" << endl;
        }
};

int main(void) {
        Mighty myHero("Arthur The Mighty", 50, 1000, 85, "Master Swordsman", 90, "Grand Sorcerer");
        
        myHero.displayMightyStats();
        
        cout << "\n--- Action Demonstration ---" << endl;
        myHero.slash();
        myHero.fireball();

        cout << "\n--- NPC Demonstration ---" << endl;
        NPC villager("Bob", 1, 100, "Wander around town", "Hello there, traveler!");
        villager.speak();
        
        cout << "\n--- Archer Demonstration ---" << endl;
        Archer ranger("Legolas", 30, 800, 95, "Master Archer");
        ranger.rapidShot();

        return 0;
}


