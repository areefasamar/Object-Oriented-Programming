#include <iostream>
#include <cstdlib> 
#include <ctime>    
using namespace std;
class HittingGame {
    private:
        int totalPlayers;
        int yourTeamHits;
        int enemyTeamHits;
   
    public:
        HittingGame() {
        srand(time(0));
        totalPlayers = rand() % 5 + 1;
        yourTeamHits = 0;
        enemyTeamHits = 0;
        }

         void playGame() {
        cout << "Total No. Of Players in your team: " << totalPlayers << endl;
        for (int i = 0; i < totalPlayers; i++) {
            int number1 = rand() % 6 + 1;  
            int number2 = rand() % 6 + 1;  
            cout << "\nPair of numbers:\n";
            cout << "Number1: " << number1 << endl;
            cout << "Number2: " << number2 << endl;
            if (number1 == number2) {
                cout << "Enemy got hit by your team!" << endl;
                yourTeamHits++;
            } 
			else {
                cout << "You got hit by the enemy team!" << endl;
                enemyTeamHits++;
            }
            }

        
        cout << "\nGame Over! ";
        if (yourTeamHits > enemyTeamHits)
            cout << "You won" << endl;
        else if (yourTeamHits < enemyTeamHits)
            cout << "You lost" << endl;
        else
            cout << "It's a tie!" << endl;
        }
};

int main() {
    HittingGame game;
    game.playGame();
    return 0;
}
