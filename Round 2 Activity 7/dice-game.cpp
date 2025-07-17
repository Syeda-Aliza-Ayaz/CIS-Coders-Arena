#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

class Player {
private:
    static int idCounter;
    string name;
    int totalScore;

public:
    int turnsPlayed;  // Tracks number of turns per player

    Player() {
        idCounter++;
        cout << "Enter name for Player " << idCounter << " (Leave blank for default): ";
        getline(cin >> ws, name);

        if (name.empty()) {
            name = "Player" + to_string(idCounter);
        }

        totalScore = 0;
        turnsPlayed = 0;
    }

    string getName() const {
        return name;
    }

    int getTotalScore() const {
        return totalScore;
    }

    bool takeTurn(int target, bool canWin) {
        int currentTurnScore = 0;
        turnsPlayed++;

        cout << "\n" << name << "'s Turn (" << "Total Score: " << totalScore << ", Turn " << turnsPlayed << ")\n";

        while (true) {
            cout << "Do you want to roll? (y to roll, any other key to stop): ";
            char choice;
            cin >> choice;

            if (tolower(choice) != 'y') {
                totalScore += currentTurnScore;
                cout << name << " ends turn with total score: " << totalScore << endl;
                break;
            }

            int roll = rollDice();
            cout << name << " rolled: " << roll << endl;

            if (roll == 1) {
                cout << "Oops! Rolled a 1. Turn over, no points earned this turn.\n";
                currentTurnScore = 0;
                break;
            }
            else {
                currentTurnScore += roll;
                cout << "Current Turn Score: " << currentTurnScore << endl;
            }
        }

        // Only check for win condition if canWin is true
        if (canWin && totalScore >= target) {
            return true;  // Player wins
        }

        return false; // Game continues
    }

private:
    int rollDice() {
        return (rand() % 6) + 1; // 1 to 6
    }
};

int Player::idCounter = 0;

int main() {
    system("chcp 65001");
    srand(time(0));

    int numPlayers;
    cout << "Enter number of players (2-4): ";
    while (!(cin >> numPlayers) || numPlayers < 2 || numPlayers > 4) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Enter number of players (2-4): ";
    }

    int targetScore;
    cout << "Set the target score to win: ";
    cin >> targetScore;

    if (targetScore <= 0) {
        cout << "Invalid target. Defaulting to 10.\n";
        targetScore = 10;
    }

    vector<Player*> players;
    for (int i = 0; i < numPlayers; i++) {
        players.push_back(new Player());
    }

    bool gameOver = false;
    int round = 1;

    while (!gameOver) {
        cout << "\n=== Round " << round << " ===\n";

        for (auto player : players) {
            bool canWin = (round > 3); // No win allowed before round 4
            if (player->takeTurn(targetScore, canWin)) {
                cout << "\n🏆 " << player->getName() << " wins the game with " << player->getTotalScore() << " points! 🏆\n";
                gameOver = true;
                break;
            }
        }

        // scoreboard after each round
        cout << "\n--- Scoreboard ---\n";
        for (auto player : players) {
            cout << player->getName() << ": " << player->getTotalScore() << " points (Turns: " << player->turnsPlayed << ")\n";
        }
        cout << "-------------------\n";

        // If game not over, check for round advancement
        if (!gameOver) {
            round++;
        }
    }

    for (auto player : players) {
        delete player;
    }

    return 0;
}
