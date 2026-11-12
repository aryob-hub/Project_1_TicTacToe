#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//tic tac toe
// Initializes the board with empty placeholder spaces
void initialize_board(char board[9]){
    // Loop to fill the board
    for (int i = 0; i < 9; i++) {
        board[i] = ' ';
    }
}

// Sets up the board in the standard output and displays those empty spaces as numbers
void display_board(const char board[9]){
    char c[9];
    //Sets the spaces to displayable numbers
    for (int i = 0; i < 9; i++) {
        c[i] = board[i];
        if (c[i] == ' ') {
            c[i] = '0' + i;
        }
    }
    // Displays the board in a 3x3 grid format
    printf("\n");
    printf(" %c | %c | %c \n", c[0], c[1], c[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", c[3], c[4], c[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", c[6], c[7], c[8]);
    printf("\n");
}
// Checks if the current player has won the game
bool check_winner(const char board[9], char player){
    //Checks all the winning conditions
    if ((board[0] == player && board[1] == player && board[2] == player) ||
        (board[3] == player && board[4] == player && board[5] == player) ||
        (board[6] == player && board[7] == player && board[8] == player) ||
        (board[0] == player && board[3] == player && board[6] == player) ||
        (board[1] == player && board[4] == player && board[7] == player) ||
        (board[2] == player && board[5] == player && board[8] == player) ||
        (board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player)) {
        // If someone won.
        return true;
    }
    // If no one won yet.
    return false;
}
// Function to switch to the other player.
char other_player(char player){
    if (player == 'X') {
        return 'O';
    }
    return 'X';
}
// Function to get the human players move.
int get_player_move(const char board[9]){
    int move;
    int result;
    int ch;
    bool cont = false;
// Loop until a valid move is entered by the player.
    while (cont == false) {
        printf("Your Turn, Enter your move (0-8): ");
        //Gets the input from user.
        result = scanf("%d", &move);
        //Checks if the input is valid and within range.
        //Checks if user inputed a integer and not something arbitrary like no input or a letter or something.
        if (result != 1) {
            printf("Invalid input. Please enter a number.\n");
            // Clears the input for second try.
            while ((ch = getchar()) != '\n' && ch != EOF);
            continue;
        }
        //Checks if the input is within the valid range of 0-8.
        if (move < 0 || move > 8) {
            // if its not within range
            printf("Invalid move. Please try again.\n");
            continue;
        }
        if (board[move] != ' ') {
            // if the space is already taken
            printf("That space is already taken. Please try again.\n");
            continue;
        }
        cont = true;
    }
// Returns the valid move entered by the player.   
    return move;
}

// Function to get the computers move 
int get_computer_move(const char board[9]){
    int move;
    // Randomly selects a move for the computer until it finds an empty space.
    do {
        move = rand() % 9;
    } while (board[move] != ' ');

    return move;
}
// Function to take turn of a player
void take_turn(char board[9], char player){
    int move;
    // If its humans turn get the humans move
    if (player == 'O') {
        move = get_player_move(board);
    }
    // If its the computers turn get the comptuers move.
    else {
        move = get_computer_move(board);
        printf("Computer chose: %d, your turn next.\n", move);
    }
    //Sents the move to the symbol of the player, essentially so the program can update the visible board.
    board[move] = player;
}
// Function to play the game
void play_game(void){
    // Sets up the initial board and sets human to go first.
    char board[9];
    char player = 'O';

    initialize_board(board);
    display_board(board);
// Loop through turns of the game.
    for(int turn = 0; turn < 9; turn++) {
        // Takes the turn of the current player and displays the updated board.
        take_turn(board, player);
        display_board(board);
        // Checks if the current player has won the game.
        if (check_winner(board, player)) {
            if (player == 'O') {
                printf("Player wins!\n");
            } else {
                printf("Computer wins!\n");
            }
            return;
        }
        // Switches player after turn.
        player = other_player(player);
    }
    // If all turns are taken and no one has won its a draw.
    printf("It's a draw!\n");
}
// If the player wants to play again
bool play_again(void){
    char response;
    // Checks if player wants to play again
    while (true) {
        printf("Do you want to play again? (y/q): ");
        // Gets the response from user.
        int result = scanf(" %c", &response);
        // If scanf fails to read we just end the program here to avoid an infinite loop.
        if (result != 1) {
            return false;
        }
        // If user wants to play again
        if (response == 'y') {
            return true;
        }
        // If the user wants to quit.
        if (response == 'q') {
            return false;
        }
        // If the user inputed something other than y or q, it will run again and ask for input.
        printf("Invalid input. Please enter y or q.\n");
    }
}
// Main function to start game.
int main(void) {
    // Seed generator for the random function, so the computer doesnt essentially make the same sequence of "random" moves each time the program is run.
    srand(time(NULL));
     
    // Welcome messages.
    printf("Welcome to Tic Tac Toe.\n");
    printf("Try to win against the computer.\n");

    // Do while loop to play the game again until the player wants to quit.
    do {
        play_game();
    } while (play_again());
    // Thank you message. 
    printf("Thanks for playing!\n");
    return 0;
}
