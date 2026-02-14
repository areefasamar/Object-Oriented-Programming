#include <iostream>
#include <iomanip>
using namespace std;

class Time {
private:
    int hour, minute, second;

public:
    // Default arguments: h=0, m=0, s=0
    Time(int h = 0, int m = 0, int s = 0) {
        setHour(h).setMinute(m).setSecond(s);
    }

    // Returning *this for cascading
    Time& setHour(int h) {
        hour = (h >= 0 && h < 24) ? h : 0;
        return *this; 
    }

    Time& setMinute(int m) {
        minute = (m >= 0 && m < 60) ? m : 0;
        return *this;
    }

    Time& setSecond(int s) {
        second = (s >= 0 && s < 60) ? s : 0;
        return *this;
    }

    void display() const {
        cout << setfill('0') << setw(2) << hour << ":" << setw(2) << minute << endl;
    }
};

int main() {
    Time t;
    // Method cascading/chaining demonstration
    t.setHour(18).setMinute(30).setSecond(22); 
    t.display();
    return 0;
}
