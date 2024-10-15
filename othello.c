// include libraries
#include <stdio.h>
#include <stdlib.h>

// function prototypes
void welcomeScreen();
void displayExplicitBoard();
void clearScreen();

// main function
int main()
{
    // call function welcomeScreen
    welcomeScreen();
    // call function clearScreen
    clearScreen();
    // call function displayExplicitBoard
    displayExplicitBoard();

    //program executed successfully
    return 0;
}

// welcomeScreen function displays the Othello logo and the rules of the game
void welcomeScreen()
{
    // print Othello logo
    printf("\t\t OOOO  TTTTTT HH  HH EEEEEE LL      LL      OOOO  \n");
    printf("\t\tOO  OO   TT   HH  HH EE     LL      LL     OO  OO \n");
    printf("\t\tOO  OO   TT   HHHHHH EEEE   LL      LL     OO  OO \n");
    printf("\t\tOO  OO   TT   HH  HH EE     LL      LL     OO  OO \n");
    printf("\t\t OOOO    TT   HH  HH EEEEEE LLLLLLL LLLLLL  OOOO  \n");
    printf("\n\n"); // new lines

    // print Othello game rules
    printf("OTHELLO GAME RULES:\n");
    printf("\t1. A square 8 x 8 board \n");
    printf("\t2. 64 discs colored black (X) on one side and white (O) on the opposite side. \n");
    printf("\t3. The board will start with 2 black discs (X) and 2 white discs (O) at the center of the board. \n");
    printf("\t4. They are arranged with black (X) forming a North-East to South-West direction. White (O) is forming a North-West to South-East direction. \n");
    printf("\t5. The goal is to get the majority of color discs on the board at the end of the game. \n");
    printf("\t6. Each player gets 32 discs and black (X) always starts the game. \n ");
    printf("\t7. The game alternates between white (O) and black (X) until one player can not make a valid move to outflank the opponent or both players have no valid moves. \n");
    printf("\t8. When a player has no valid moves, they pass their turn and the opponent continues. \n");
    printf("\t9. A player cannot voluntarily forfeit their turn. \n");
    printf("\t10. When both players can not make a valid move the game ends. \n\n");
}

// function displayExplicitBoard displays a hardcoded version of an Othello game board
void displayExplicitBoard()
{
    // new line improves readability
    printf("\n");

    // print Othello game board
    printf("|-----------------------------------------------------| \n");
    printf("|     |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  | \n");
    printf("|-----------------------------------------------------| \n");
    printf("|  1  |     |     |     |     |     |     |     |     | \n");
    printf("|-----------------------------------------------------| \n");
    printf("|  2  |     |     |     |     |     |     |     |     | \n");
    printf("|-----------------------------------------------------| \n");
    printf("|  3  |     |     |     |     |     |     |     |     | \n");
    printf("|-----------------------------------------------------| \n");
    printf("|  4  |     |     |     |  O  |  X  |     |     |     | \n");
    printf("|-----------------------------------------------------| \n");
    printf("|  5  |     |     |     |  X  |  O  |     |     |     | \n");
    printf("|-----------------------------------------------------| \n");
    printf("|  6  |     |     |     |     |     |     |     |     | \n");
    printf("|-----------------------------------------------------| \n");
    printf("|  7  |     |     |     |     |     |     |     |     | \n");
    printf("|-----------------------------------------------------| \n");
    printf("|  8  |     |     |     |     |     |     |     |     | \n");
    printf("|-----------------------------------------------------| \n");
}

// function clearScreen clears the screen for display purposes
void clearScreen()
{
    // prompt user to hit the enter key
    printf("\t                        Hit <ENTER> to continue! \n");

    char enter;
    scanf("%c", &enter);

    //Windows
    system("cls");
    // UNIX flavor (i.e. MacOS, Linux, etc.)
    //system("clear")
}
