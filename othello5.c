#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define NAME 20
#define ROW 8
#define COL 8
#define SPACE ' '
#define PLAYER_X 1
#define PLAYER_O 2
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define INVALID -1
#define MIN 0
#define MAX 7
#define EIGHT 8
// player structure
struct player {
    int playerNum;
    char playerName[20];
    int discCount;
    char playChar;
};
// function prototypes
void welcomeScreen();
void displayExplicitBoard();
void clearScreen();
void playGame();
void initializeBoard(char board[ROW][COL]);
void displayBoard(char board[ROW][COL]);
void makeMove(struct player *player, char board[ROW][COL]);
int isValid(char move[3], char board[ROW][COL], struct player *player);
int isOpen(char move[3], char board[ROW][COL]);
int getMoveRow(char move[3]);
int getMoveCol(char move[3]);
void displayStats(struct player player);
int isOutFlank(char move[3], char board[ROW][COL], char playerChar);
int checkHorizontal(int row, int col, char board[ROW][COL], char playerChar);
int checkVertical(int row, int col, char board[ROW][COL], char playerChar);
int checkDiagonal(int row, int col, char board[ROW][COL], char playerChar);
void updateBoard(char move[3], char board[ROW][COL], struct player *player);
void updateHorizontal(int row, int col, char board [ROW][COL], struct player *player);
void updateVertical(int row, int col, char board [ROW][COL], struct player *player);
void updateDiagonal(int row, int col, char board [ROW][COL], struct player *player);
void updateDiscCount(char board[ROW][COL], struct player *player);

// main function
int main()
{
    // call function welcomeScreen
    welcomeScreen();
    // call function clearScreen
    clearScreen();
    // call function displayExplicitBoard

    // displayExplicitBoard();

    // call function playGame
    playGame();

    // program executed successfully
    return 0;
}

// welcomeScreen function displays the Othello logo and rules of the game
void welcomeScreen ()
{
	printf ("\t\t OOOO  TTTTTT HH  HH EEEEEE LL      LL      OOOO  \n");
	printf ("\t\tOO  OO   TT   HH  HH EE     LL      LL     OO  OO \n");
	printf ("\t\tOO  OO   TT   HHHHHH EEEE   LL      LL     OO  OO \n");
	printf ("\t\tOO  OO   TT   HH  HH EE     LL      LL     OO  OO \n");
	printf ("\t\t OOOO    TT   HH  HH EEEEEE LLLLLLL LLLLLL  OOOO  \n");
	printf ("\n\n");//
	printf ("OTHELLO GAME RULES:\n");
    printf("\t1. A square 8 x 8 board\n");
    printf("\t2. 64 discs colored black (X) on one side and white (O) on the opposite side.\n");
    printf("\t3. The board will start with 2 black discs (X) and 2 white discs (O) at the center of the board.\n");
    printf("\t4. They are arranged with black (X) forming a North-East to South-West direction. White (O) is forming a North-West to South-East direction\n");
    printf("\t5. The goal is to get the majority of color discs on the board at the end of the game.\n");
    printf("\t6. Each player gets 32 discs and black (X) always starts the game.\n");
    printf("\t7. The game alternates between white (O) and black (X) until one player can not make a valid move to outflank the opponent or both players have no valid moves.\n");
    printf("\t8. When a player has no valid moves, they pass their turn and the opponent continues.\n");
    printf("\t9. A player cannot voluntarily forfeit their turn.\n");
    printf("\t10. When both players can not make a valid move the game ends.\n");
}

// function displayExplicitBoard displays a hardcoded version of an Othello board
void displayExplicitBoard()
{
    printf("|-----------------------------------------------------|\n");
    printf("|     |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  1  |     |     |     |     |     |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  2  |     |     |     |     |     |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  3  |     |     |     |     |     |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  4  |     |     |     |  O  |  X  |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  5  |     |     |     |  X  |  O  |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  6  |     |     |     |     |     |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  7  |     |     |     |     |     |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  8  |     |     |     |     |     |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
 }

// function clearScreen clears the screen for display purposes
void clearScreen()
{
    printf("\n\t\t\t\tHit <ENTER> to continue!\n");

	char enter;
	scanf("%c", &enter );

	// send the clear screen command Windows
    system("cls");
    // send the clear screen command for UNIX flavor operating systems
    // system("clear");
}
// function to play the game
void playGame()
{
    // get player names
    struct player playerX;
    struct player playerO;
    // Othello board
    char board[ROW][COL]; // this is really a memory location of board[0][0]
    // black (X) always goes first
    int currentPlayer = PLAYER_X;
    int loop = ZERO;
    // initializing playerNum & discCount
    playerX.playerNum = PLAYER_X;
    playerO.playerNum = PLAYER_O;
    playerX.discCount = TWO;
    playerO.discCount = TWO;
    // prompting Player X to enter their name
    printf("Player X, please enter your name\n");
    scanf("%s", playerX.playerName);
    // prompting Player O to enter their name
    printf("Player O, please enter your name\n");
    scanf("%s", playerO.playerName);

    playerX.playChar = 'X';
    playerO.playChar = 'O';

    printf("%s and %s, let's play Othello!\n", playerX.playerName, playerO.playerName);



    // call function initializeBoard
    initializeBoard(board);
    // while loop to run through players' turns
    while(loop < EIGHT)
    {
        // Displays board each turn
        displayBoard(board);

        // request the player's move
        if(currentPlayer == PLAYER_X)
        {
            makeMove(&playerX, board);
            currentPlayer = PLAYER_O;
        }
        else if(currentPlayer == PLAYER_O)
        {
            makeMove(&playerO, board);
            currentPlayer = PLAYER_X;
        }

        // Displaying each player's stats before the loop increment
        updateDiscCount(board, &playerX);
        updateDiscCount(board, &playerO);


        loop++;
    }


    displayBoard(board);
    updateDiscCount(board, &playerX);
    updateDiscCount(board, &playerO);
    displayStats(playerX);
    displayStats(playerO);
}
// initializes board with pre-defined values
void initializeBoard(char board[ROW][COL])
{
    for(int row = 0; row < ROW; row++)
    {
        for(int col = 0; col < COL; col++)
        {
            if((row == THREE && col == THREE) || (row == FOUR && col == FOUR))
                board[row][col] = 'O';
            else if((row == THREE && col == FOUR) || row == FOUR && col == THREE)
                board[row][col] = 'X';
            else
                board[row][col] = SPACE;
        }
    }
}

void displayBoard(char board[ROW][COL])
{
    printf("|-----------------------------------------------------|\n");
    printf("|     |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |\n");

    for(int row = 0; row < ROW; row++)
    {
        printf("|-----------------------------------------------------|\n");
        printf("|  %d  |", (row + 1));

        for(int col = 0; col < COL; col++)
        {
            printf("  %c  |", board[row][col]);
        }

        printf("\n");
    }

    printf("|-----------------------------------------------------|\n");
}
// validates the player's move
void makeMove(struct player *player, char board[ROW][COL])
{
    char move[THREE];
    int valid = FALSE;

    // loop until the player enters a valid move
    while(valid == FALSE)
    {
        printf("%s, enter your move location (e.g. B6)\n", player -> playerName);
        scanf("%s", move);

        printf("%s, you entered %s\n", player -> playerName, move);

        // clears the buffer of extra characters
        getchar();
//        fflush(stdin);

        int length = (int)strlen(move);

        if(length == TWO) {
            valid = isValid(move, board, player);
        }
        else
            valid = FALSE;

        if(valid == FALSE)
            printf("Invalid move, try again\n\n");
        if(valid == TRUE)
            printf("Selected move is valid!\n\n");


    }
}
// validates if move is valid
int isValid(char move[3], char board[ROW][COL], struct player *player) {
    int valid = FALSE;

    valid = isOpen(move, board);

    valid = isOutFlank(move, board, player->playChar);
    if (valid)
        updateBoard(move, board, player);

    return valid;
}
// validates if move is valid and open
int isOpen(char move[3], char board[ROW][COL]) {
    int open = FALSE;

    int rowInt = getMoveRow(move);
    int colInt = getMoveCol(move);

    if(rowInt != INVALID && colInt != INVALID && board[rowInt][colInt] == SPACE)
        open = TRUE;

    return open;
}
// displays a player's stats
void displayStats(struct player player) {
    printf("Player name: %s\n", player.playerName);
    printf("Player number: %d\n", player.playerNum);
    printf("Player character: %s\n", player.playChar);
    printf("Player discs: %d\n\n", player.discCount);
}
// validates if move row is valid
int getMoveRow(char move[THREE]) {
  // initialize to an invalid value
    int rowInt = INVALID;
    // use the array to get the index value for the board array column
    //              0    1    2    3    4    5    6    7
    char rows[] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    for(int row = 0; row < ROW; row++)
    {
        // the second character in the move array is the column
        if(move[ONE] == rows[row])
            rowInt = row;
    }
    return rowInt;
}
// validates if move col is valid
int getMoveCol(char move[THREE]) {
  // initialize to an invalid value
    int colInt = INVALID;
    // use the array to get the index value for the board array row
    //              0    1    2    3    4    5    6    7
    char cols[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    for(int col = 0; col < COL; col++)
    {
        // convert the first character to upper case
        if(toupper(move[ZERO]) == cols[col])
            colInt = col;
    }
    return colInt;
}

int isOutFlank(char move[3], char board[ROW][COL], char playerChar) {
        int flank = FALSE;
        int rowInt = getMoveRow(move);
        int colInt = getMoveCol(move);

        if ((checkHorizontal(rowInt, colInt, board, playerChar) > ZERO) || (checkVertical(rowInt, colInt, board, playerChar)) || checkDiagonal(rowInt, colInt, board, playerChar))
            flank = TRUE;

        return flank;
}

int checkHorizontal(int row, int col, char board[ROW][COL], char playerChar) {
    int discCount = 0;
    int i;

    for(i = (col-1); i <= ZERO; --i) {
        if(board[row][i] == SPACE)
            break;

        if(board[row][i] == playerChar)
            break;

        if(board[row][i] != playerChar)
            discCount++;
    }

    for(i = (col+1); i <= 7; ++i) {
        if(board[row][i] == SPACE)
            break;

        if(board[row][i] == playerChar)
            break;

        if(board[row][i] != playerChar)
            discCount++;
    }
}

int checkVertical(int row, int col, char board[ROW][COL], char playerChar) {
    int discCount = 0;
    int i;

    for(i = (row-1); i <= ZERO; --i) {
        if(board[i][col] == SPACE)
            break;

        if(board[i][col] == playerChar)
            break;

        if(board[i][col] != playerChar)
            discCount++;
    }

    for(i = (row+1); i <= 7; ++i) {
        if(board[i][col] == SPACE)
            break;

        if(board[i][col] == playerChar)
            break;

        if(board[i][col] != playerChar)
            discCount++;
    }
}

int checkDiagonal(int row, int col, char board[ROW][COL], char playerChar) {

}

void updateBoard(char move[3], char board[ROW][COL], struct player *player) {
    int rowInt = getMoveRow(move);
    int colInt = getMoveCol(move);

    if (checkHorizontal(rowInt, colInt, board, player->playChar) > ZERO)
        updateHorizontal(rowInt, colInt, board, player);

    if (checkVertical(rowInt, colInt, board, player->playChar) > ZERO)
        updateVertical(rowInt, colInt, board, player);

    if (checkDiagonal(rowInt, colInt, board, player->playChar) > ZERO)
        updateDiagonal(rowInt, colInt, board, player);
}

void updateHorizontal(int row, int col, char board[ROW][COL], struct player *player) {
    int i;

    board[row][col] = player->playChar;

    for(i = (col-1); i <= ZERO; --i) {
        if(board[row][i] == SPACE)
            break;

        if(board[row][i] == player->playChar)
            break;

        if(board[row][i] != player->playChar)
            board[row][i] = player->playChar;
    }

    for(i = (col+1); i <= 7; ++i) {
        if(board[row][i] == SPACE)
            break;

        if(board[row][i] == player->playChar)
            break;

        if(board[row][i] != player->playChar)
            board[row][i] = player->playChar;
    }
}

void updateVertical(int row, int col, char board[ROW][COL], struct player *player) {
    int i;

    board[row][col] = player->playChar;

    for(i = (row-1); i <= ZERO; --i) {
        if(board[i][col] == SPACE)
            break;

        if(board[i][col] == player->playChar)
            break;

        if(board[i][col] != player->playChar)
            board[i][col] = player->playChar;
    }

    for(i = (row+1); i <= 7; ++i) {
        if(board[i][col] == SPACE)
            break;

        if(board[i][col] == player->playChar)
            break;

        if(board[i][col] != player->playChar)
            board[i][col] = player->playChar;
    }
}

void updateDiagonal(int row, int col,char board[ROW][COL], struct player *player) {

}

void updateDiscCount(char board[ROW][COL], struct player *player) {
    int i;
    int j;
    int count = 0;

    for(i = 0; i < ROW; ++i) {
        for(j = 0; j < COL; ++j) {
            if(board[i][j] == player->playChar)
                count++;
        }
    }

    player->discCount = count;
}
