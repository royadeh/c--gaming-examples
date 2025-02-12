#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

const int BOARD_SIZE = 50;
const int CHEESE_WHEEL_POSITION = 49;
const int MAX_TRAP_COMPONENTS = 23;
const int DIE_SIDES = 6;
const int START_CHEESE_SUPPLY = 52;
const int MAX_CHEESE = 6;

class Mouse {
public:
    int position;
    int cheese;
    bool inGame;

    Mouse() : position(0), cheese(0), inGame(true) {}
};

class Game {
private:
    vector<Mouse> mice;
    int cheeseSupply;
    int trapComponents;
    int playerCount;

public:
    Game(int numPlayers) : playerCount(numPlayers), cheeseSupply(START_CHEESE_SUPPLY), trapComponents(MAX_TRAP_COMPONENTS) {
        mice.resize(numPlayers);
        srand(time(0));
    }

    int rollDie() {
        return rand() % DIE_SIDES + 1;
    }

    void moveMouse(int mouseIdx) {
        if (!mice[mouseIdx].inGame) return;

        int roll = rollDie();
        cout << "Mouse " << mouseIdx + 1 << " rolls a " << roll << "!" << endl;
        mice[mouseIdx].position += roll;
        if (mice[mouseIdx].position >= BOARD_SIZE) {
            mice[mouseIdx].position = CHEESE_WHEEL_POSITION;
            cout << "Mouse " << mouseIdx + 1 << " reached the cheese wheel!" << endl;
        }
        determineSpaceType(mouseIdx);
    }

    void determineSpaceType(int mouseIdx) {
        int pos = mice[mouseIdx].position;
        if (pos == CHEESE_WHEEL_POSITION) {
            mice[mouseIdx].cheese = MAX_CHEESE;
        } else if (pos % 5 == 0 && cheeseSupply > 0) {
            mice[mouseIdx].cheese++;
            cheeseSupply--;
            cout << "Mouse " << mouseIdx + 1 << " found cheese!" << endl;
        } else if (pos % 8 == 0 && trapComponents > 0) {
            trapComponents--;
            cout << "Mouse " << mouseIdx + 1 << " collected a trap component!" << endl;
        }
    }

    bool trapStep(int failureChance, string failureMessage) {
        if (rand() % 100 < failureChance) {
            cout << failureMessage << endl;
            return false;
        }
        return true;
    }

    bool activateTrap() {
        cout << "Activating trap..." << endl;
        this_thread::sleep_for(chrono::seconds(2));

        return trapStep(10, "The lever failed!") &&
               trapStep(15, "The boot missed the bucket!") &&
               trapStep(20, "The marble fell off the stairs!") &&
               trapStep(25, "The second marble didn't move!") &&
               trapStep(30, "The diver missed the washtub!") &&
               trapStep(35, "The cage got stuck!");
    }

    void playTurn(int mouseIdx) {
        moveMouse(mouseIdx);
        if (mice[mouseIdx].cheese >= MAX_CHEESE && activateTrap()) {
            mice[mouseIdx].inGame = false;
            cout << "Mouse " << mouseIdx + 1 << " has been trapped!" << endl;
        }
    }

    void playGame() {
        while (true) {
            bool allTrapped = true;
            for (int i = 0; i < playerCount; i++) {
                if (mice[i].inGame) {
                    allTrapped = false;
                    playTurn(i);
                }
            }
            if (allTrapped) break;
        }
        cout << "Game Over!" << endl;
    }
};

int main() {
    int numPlayers;
    cout << "Enter number of players: ";
    cin >> numPlayers;
    Game game(numPlayers);
    game.playGame();
    return 0;
}
