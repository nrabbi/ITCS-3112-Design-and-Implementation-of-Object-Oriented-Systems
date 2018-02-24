// Nazmul Rabbi
// ITCS 3112
// P1: TicTacToe
// August 28 2017

#include <iostream>
using namespace std;

void playTicTacToe (char *input, int &position, int &counter);
void draw (char* input);
int menu (int& input);
int player (int& counter);

int main() {
    
    int player_counter = 1;
    int choice = 0;
    int position;
    char tic_tac_toe[9] = {'-','-','-','-','-','-','-','-','-'};
    
    do {
        cout << "Turn of Player " << player_counter << endl << endl;
        menu(choice);
        cout << "You chose option : " << choice << endl << endl;
        
        if (choice == 1)
            // draws the array
            draw(tic_tac_toe);
        
        if (choice == 2) {
            // makes sure grid position is valid
            do {
                cout << "Pick Grid Position: ";
                cout << "\n\n1|2|3\n4|5|6\n7|8|9\n\n";
                cin >> position;
                
                // check for invalid grid position input
                if (position > 9 || position < 1) {
                    cout << "\nChoose a valid grid position.";
                    // changes player turn
                    player(player_counter);
                    cout << "\n\nTurn of Player: " << player_counter << endl << endl;
                }
                
            } while (position > 9 || position < 1);
            
            cout << "You chose grid position: " << position << endl << endl;
            position -= 1;
            
            // calls the function for the game logic
            playTicTacToe(tic_tac_toe, position, player_counter);
            
            // draws the array
            draw(tic_tac_toe);
            
            // check for game ending
            if (player_counter == 3)
                return 0;
        }
        if (choice == 3) {
            cout << "Program terminated...\n\n";
            return 0;
        }
        
        // check for valid menu option selection
        if (choice > 3 || choice < 1)
            cout << "ERROR! Please Select a Valid Option.\n\n";
        
    }while (choice != 3);
    
    return 0;
}

void playTicTacToe (char* input, int& position, int& counter) {
    // logic for making a move (only when the block is empty)
    if (input[position] == '-') {
        // logic for making a move
        if (counter == 1)
            input[position] = 'X';
        else
            input[position] = 'O';
        
        // changes player turn
        player(counter);
    }
    // logic for invalid moves
    else if (input[position] == 'X' || input[position] == 'O') {
        cout << "ERROR! Grid Position is not empty so move is not valid. Please try again!\n\n";
        // changes player turn
        player(counter);
    }
    
    // player 1 win logic
    if ((input[0] == 'X' && input[4] == 'X' && input[8] == 'X') || (input[2] == 'X' && input[4] == 'X' && input[6] == 'X') || (input[0] == 'X' && input[3] == 'X' && input[6] == 'X') || (input[1] == 'X' && input[4] == 'X' && input[7] == 'X') || (input[2] == 'X' && input[5] == 'X' && input[8] == 'X') || (input[0] == 'X' && input[1] == 'X' && input[2] == 'X') || (input[3] == 'X' && input[4] == 'X' && input[5] == 'X') || (input[6] == 'X' && input[7] == 'X' && input[8] == 'X')) {
        cout << "Player 1 has won the game...\n\n";
        // when counter value is not 1 or 2 it signals that the game has ended
        counter = 3;
    }
    // player 2 win logic
    else if ((input[0] == 'O' && input[4] == 'O' && input[8] == 'O') || (input[2] == 'O' && input[4] == 'O' && input[6] == 'O') || (input[0] == 'O' && input[3] == 'O' && input[6] == 'O') || (input[1] == 'O' && input[4] == 'O' && input[7] == 'O') || (input[2] == 'O' && input[5] == 'O' && input[8] == 'O') || (input[0] == 'O' && input[1] == 'O' && input[2] == 'O') || (input[3] == 'O' && input[4] == 'O' && input[5] == 'O') || (input[6] == 'O' && input[7] == 'O' && input[8] == 'O')) {
        cout << "Player 2 has won the game...\n\n";
        // when counter value is not 1 or 2 it signals that the game has ended
        counter = 3;
    }
    // game draw logic
    else if ((input[0] != '-' && input[1] != '-' && input[2] != '-' && input[3] != '-' && input[4] != '-' && input[5] != '-' && input[6] != '-' && input[7] != '-' && input[8] != '-')) {
        cout << "Game is drawn...\n\n";
        // when counter value is not 1 or 2 it signals that the game has ended
        counter = 3;
    }
}

// This function draws the tic-tac-toe square
void draw (char* input) {
    for (int k = 0; k < 9; k++) {
        cout << input[k] << "|" << input[k+1] << "|" << input[k+2] << endl;
        k=k+2;
    }
    cout << endl;
}

// this function is used to run the app menu
int menu (int& input) {
    cout << "Options\n1: Display the board\n2: Make a Move\n3: End Game\n\n";
    cout << "Please select an option: ";
    cin >> input;
    cout << endl;
    
    return input;
}

// logic for player turn
int player (int& counter) {
    if (counter == 1)
        counter++;
    else
        counter--;
    
    return counter;
}
