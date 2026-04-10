#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Patient {
private:
    string name;
    int age;

protected:
    double risk;

public:
    Patient() {
        name = "";
        age = 0;
        risk = 0.0;
    }

    Patient(string n, int a) {
        name = n;
        age = a;
        risk = 0.0;
    }

    virtual ~Patient() {}

    string getName() { return name; }
    int getAge() { return age; }

    virtual void displayInfo() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }

    virtual double CalculateRisk() = 0;
};

class CardiacPatient : public Patient {
private:
    double cholesterolLevel;
    int bloodPressure;

public:
    CardiacPatient(string n, int a, double cl, int bp) 
        : Patient(n, a), cholesterolLevel(cl), bloodPressure(bp) {}

    double CalculateRisk() override {
        risk = (cholesterolLevel * 0.3) + (bloodPressure * 0.2);
        return risk;
    }

    void displayInfo() override {
        Patient::displayInfo();
        cout << "Condition: Cardiac" << endl;
        cout << "Risk Score: " << CalculateRisk() << endl;
    }
};

class DiabeticPatient : public Patient {
private:
    double sugarLvl;
    int bmi;

public:
    DiabeticPatient(string n, int a, double sl, int b) 
        : Patient(n, a), sugarLvl(sl), bmi(b) {}

    double CalculateRisk() override {
        risk = (sugarLvl * 0.5) + (bmi * 0.1);
        return risk;
    }

    void displayInfo() override {
        Patient::displayInfo();
        cout << "Condition: Diabetic" << endl;
        cout << "Risk Score: " << CalculateRisk() << endl;
    }
};

class RespiratoryPatient : public Patient {
private:
    int oxygenLvl;
    int smokingYears;

public:
    RespiratoryPatient(string n, int a, int o, int s) 
        : Patient(n, a), oxygenLvl(o), smokingYears(s) {}

    double CalculateRisk() override {
        risk = (0.2 * (100 - oxygenLvl)) + (smokingYears * 0.4);
        return risk;
    }

    void displayInfo() override {
        Patient::displayInfo();
        cout << "Condition: Respiratory" << endl;
        cout << "Risk Score: " << CalculateRisk() << endl;
    }
};

int main() {
    Patient* patients[3];

    patients[0] = new CardiacPatient("Ali", 55, 220.5, 140);
    patients[1] = new DiabeticPatient("Sara", 40, 180.0, 28);
    patients[2] = new RespiratoryPatient("John", 65, 92, 20);

    for (int i = 0; i < 3; i++) {
        patients[i]->displayInfo();
        cout << endl;
    }

    for (int i = 0; i < 3; i++) {
        delete patients[i];
    }

    return 0;
}
