#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Declaring Global Variables
char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';
char space[] = "   |   |   \n";
char bar[] = "---|---|---\n";

// Declaring Functions
void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main(){
    // Declaring Local Variables
    char winner = ' ';
    char response = ' ';

    // Starting Game
    do{
        winner = ' ';
        response = ' ';
        resetBoard();

        while(winner == ' ' && checkFreeSpaces() != 0){
            // Build Board
            printBoard();

            // Player Moveset
            playerMove();
            winner = checkWinner();
            if(winner != ' ' && checkFreeSpaces() == 0) break;

            // Computer Moveset
            computerMove();
            winner = checkWinner();
            if(winner != ' ' && checkFreeSpaces() == 0) break;
        }
        printBoard();
        printWinner(winner);

        // Ask to rerun the program
        printf("\nWould you like to play again? (Y/N): ");
        scanf("%c");
        scanf("%c", &response);
        response = toupper(response);
    }while(response == 'Y');
    return 0;
}

// Inizializing Functions
void resetBoard(){ 
    // Loop Over all Spots
    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 3;j++){
            // Clear all Spots
            board[i][j] = ' ';
        }
    }
}
void printBoard(){
    // Loop Over all Rows
    for(int i = 0;i < 3;i++){
        // Build all Spots
        printf("%s",space);
        printf(" %c | %c | %c \n",board[0+i][0],board[0+i][1],board[0+i][2]);
        if(i != 2) printf("%s",bar);
    }
}
int checkFreeSpaces(){
    // Declaring Local Variables
    int freeSpaces = 9;

    // Loop over all Spots
    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 3;j++){
            // Check if Spot is Empty
            if(board[i][j] != ' ') freeSpaces--;
        }
    }
    return freeSpaces;
};
void playerMove(){
    // Declaring Loca Variables
    int x;
    int y;
    
    // Get Input
    do{
        printf("Enter a row number (1-3):");
        scanf("%d",&x);
        x--;
        printf("Enter a column number (1-3):");
        scanf("%d",&y);
        y--;
        if(board[x][y] != ' ') printf("This spot is already taken!\n");
        else{ 
            board[x][y] = PLAYER;
            break;
        }
    }while(board[x][y] != ' ');
}
void computerMove(){
    // Declaring Loca Variables
    srand(time(0));
    int x;
    int y;

    // Check Free Spaces
    if(checkFreeSpaces() > 0){
        // Generate Random Numbers
        do{ 
            x = rand() % 3;
            y = rand() % 3;
        }while(board[x][y] != ' ');
        board[x][y] = COMPUTER;
    }else printWinner(' '); // Declare Draw

}
char checkWinner(){
    // Checking Rows
    for(int i = 0; i < 3;i++){
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2]) return board[i][0];
    }

    // Checking Columns
    for(int i = 0; i < 3;i++){
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i]) return board[0][i];
    }

    // Checking Diagonals
    if((board[0][0] == board[1][1] && board[0][0] == board[2][2]) || (board[0][2] == board[1][1] && board[0][2] == board[2][0])) return board[1][1];


    // Default Return
    return ' ';
};
void printWinner(char winner){
    // Check Victory
    if(winner == PLAYER) printf("YOU WIN!");
    else if(winner == COMPUTER) printf("YOU LOSE!");
    else printf("IT'S A TIE!");
}
