#include <iostream>
#include <string>
using namespace std;
class SoccerPlayer {
        private:
            int number;
            string name;
            int x, y; 

        public:
            SoccerPlayer(int num, string n, int xpos, int ypos) {
                number = num;
                name = n;
                x = xpos;
                y = ypos;
            }

            void setNumber(int num) { number = num; }
            void setName(string n) { name = n; }
            void setPosition(int xpos, int ypos) { x = xpos; y = ypos; }

            int getNumber() { return number; }
            string getName() { return name; }
            void getPosition() { cout << "(" << x << ", " << y << ")"; }

            void run(int dx, int dy) {
                x += dx;
                y += dy;
                cout << name << " ran to position ";
                getPosition();
                cout << endl;
            }
            
           void kickBall() {
                cout << name << " kicks the ball!" << endl;
            }
};
int main() {
   SoccerPlayer player1(10, "Messi", 0, 0);
   player1.run(5, 3);
   player1.kickBall();
   return 0;
}
