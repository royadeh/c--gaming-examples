#include <iostream>
using namespace std;

// Constants for the game
const int NUM_ROWS = 4;
int rows[NUM_ROWS] = {1, 3, 5, 7}; // Number of sticks in each row
bool is_first_player = true;

// Function to display the current game state
void displayGameState() {
    for (int i = 0; i < NUM_ROWS; i++) {
        cout << "Number of sticks in Row " << i + 1 << ": " << rows[i] << endl;
    }
}

// Function to handle a player's move
bool makeMove(int row_number, int sticks) {
    if (row_number < 1 || row_number > NUM_ROWS) {
        cout << "Invalid row number!" << endl;
        return false;
    }
    
    int row_index = row_number - 1;
    
    if (sticks > rows[row_index]) {
        cout << "That is too many sticks!" << endl;
        return false;
    }
    
    // Subtract the number of sticks from the selected row
    rows[row_index] -= sticks;
    return true;
}

// Function to check if the game is over
bool checkGameOver() {
    for (int i = 0; i < NUM_ROWS; i++) {
        if (rows[i] > 0) return false; // If there's any row with sticks, the game is not over
    }
    return true;
}

// Function to handle player's turn
void playerTurn() {
    int row_number, sticks;
    cout << "Enter the row number (1-4): ";
    cin >> row_number;
    
    cout << "Enter the number of sticks to take: ";
    cin >> sticks;
    
    if (makeMove(row_number, sticks)) {
        is_first_player = !is_first_player; // Switch players after a valid move
    }
}

// Function to simulate the computer's move (AI logic could go here)
void computerTurn() {
    int row_number = 0, sticks = 0;

    // Simple AI: Choose a random row and take 1 stick (just for demonstration)
    for (int i = 0; i < NUM_ROWS; i++) {
        if (rows[i] > 0) {
            row_number = i + 1;
            sticks = 1;
            break;
        }
    }

    cout << "Computer removes " << sticks << " stick(s) from Row " << row_number << endl;
    makeMove(row_number, sticks);
}

// Main game loop
void startGame() {
    while (true) {
        displayGameState(); // Show the current state of the game
        
        if (is_first_player) {
            cout << "Player 1's turn:" << endl;
            playerTurn();
        } else {
            cout << "Player 2's turn (Computer):" << endl;
            computerTurn();
        }

        if (checkGameOver()) {
            cout << "Game over!" << endl;
            break; // End the game if it's over
        }
    }
}

int main() {
    startGame(); // Start the game
    return 0;
}