#include <stdio.h>
#include <stdlib.h>
#include <time.h>


    
void printBoard(int board[5][5]) {
    printf("\n");
    for (int row = 0; row <= 4; row++) {
        for (int col = 0; col <= 4; col++) {
            printf("%d ", board[row][col]);
        }
        printf("\n");
    }
    
}

void takeManualInput(int *returnLocation, int manualtile) {
    printf("Place tile %d using format 0-4 0-4:\n", manualtile);
    scanf("%d%d", &returnLocation[0], &returnLocation[1]);
    while (((returnLocation[0] > 4) || (returnLocation[0] < 0) || (returnLocation[1] > 4) || (returnLocation[1] < 0)))
    {
        printf("Tile Coordinate Misinput, try again:\n");
        scanf("%d%d", &returnLocation[0], &returnLocation[1]);
    }
}

















int main() {
    srand(time(NULL));
    int board[5][5] = {0};
    int locationtoplaceman[2] = {0, 0};
    int tiletoplaceman;



    for (int turn = 25; turn > 0; turn--) {
    tiletoplaceman = (rand() % 6) + 1;
    printf("\nYou are have %d turn(s) remaining\n\n", turn);

    takeManualInput(locationtoplaceman, tiletoplaceman);

    board[locationtoplaceman[0]][locationtoplaceman[1]] = tiletoplaceman; //Set tile in board

    printf("Placed tile in slot %d, %d \n", locationtoplaceman[0], locationtoplaceman[1]);

    printBoard(board);
    
    }


    return 0;
}