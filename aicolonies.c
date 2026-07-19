#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
    
void printBoard(int board[5][5]) {
    printf("\n");
    for (int col = 0; col <= 4; col++) {
        for (int row = 0; row <= 4; row++) {
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

int getTileInDirection(enum Direction direction, int tilepos[2], int board[5][5]) {
    switch (direction) {
        case UP:
            if (tilepos[1] < 4) {
                return board[tilepos[0]][tilepos[1] - 1];
            } else {
                return -1;
            }
            break;
        case DOWN:
            if (tilepos[1] > 0) {
                return board[tilepos[0]][tilepos[1] + 1];
            } else {
                return -1;
            }
            break;
        case LEFT:
            if (tilepos[0] > 0) {
                return board[tilepos[0] - 1][tilepos[1]];
            } else {
                return -1;
            }
            break;
        case RIGHT:
            if (tilepos[0] < 4) {
                return board[tilepos[0] + 1][tilepos[1]];
            } else {
                return -1;
            }
            break;
    }

}

int scorePort(int portpos[2], int board[5][5], int visited[24][2], int* visitedmax, int *sumpoints) {
    for (int visitcheck = 0; visitcheck < *visitedmax; visitcheck++) {
        if (!((visited[visitcheck][0] == portpos[0]) && (visited[visitcheck][1] == portpos[1]))) { //So long as the port has not been visited, we can score it
            *visitedmax++;
            visited[*visitedmax][0] = portpos[0];
            visited[*visitedmax][1] = portpos[1];
            *sumpoints++;
            //Check all directions for more ports at some point 

        }
    }
}

void scoreTile(int tilepos[2], int board[5][5]) {
    int tilescore = 0;
    switch (board[tilepos[0]][tilepos[1]]) {
        case 1:
            tilescore++;
            if (getTileInDirection(UP, tilepos, board) == 1) {
                tilescore++;
            }
            if (getTileInDirection(DOWN, tilepos, board) == 1) {
                tilescore++;
            }
            if (getTileInDirection(LEFT, tilepos, board) == 1) {
                tilescore++;
            }
            if (getTileInDirection(RIGHT, tilepos, board) == 1) {
                tilescore++;
            }
            break;
        case 2:
        /*
        
            int visitedwater[24][2] = {{0, 0}};
            int visitedmax = 0;
            int sumpoints = 0;
            scorePort(tilepos, board, visitedwater, &visitedmax, &sumpoints);
            */

           //Pointer decay will kill the recursion, new meta incoming to a theatre near you
            break;
            
        case 3:
            tilescore = 8;
            //if (tilepos[1] < 4) {
                /*
                if (getTileInDirection(UP, tilepos, board) == 3) {
                    tilescore-=2;
                }
            }*/ 




            /*
            
                    case UP:
            if (tilepos[1] < 4) {
                return board[tilepos[0]][tilepos[1] - 1];
            } else {
                return -1;
            }
            break;
        case DOWN:
            if (tilepos[1] > 0) {
                return board[tilepos[0]][tilepos[1] + 1];
            } else {
                return -1;
            }
            break;
        case LEFT:
            if (tilepos[0] > 0) {
                return board[tilepos[0] - 1][tilepos[1]];
            } else {
                return -1;
            }
            break;
        case RIGHT:
            if (tilepos[0] < 4) {
                return board[tilepos[0] + 1][tilepos[1]];
            } else {
                return -1;
            }
            break;
            */

            break;
        case 4:
            int tilecheckID[2] = {tilepos[0], tilepos[1]};
            while (getTileInDirection(UP, tilecheckID, board) == 4) {
                tilescore+=2;
                tilecheckID[1]--;
            }
            tilecheckID[1] = tilepos[1];
            while (getTileInDirection(DOWN, tilecheckID, board) == 4) {
                tilescore+=2;
                tilecheckID[1]++;
            }
            break;
        case 5:
            //cornout
        case 6:
            if (getTileInDirection(UP, tilepos, board) == 0) {
                tilescore+=2;
            }
            if (getTileInDirection(DOWN, tilepos, board) == 0) {
                tilescore+=2;
            }
            if (getTileInDirection(LEFT, tilepos, board) == 0) {
                tilescore+=2;
            }
            if (getTileInDirection(RIGHT, tilepos, board) == 0) {
                tilescore+=2;
            }
            break;
    }
    return tilescore;
}

void scoreBoard(int board[5][5], int *score, int *pointboard) {
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            int position[] = {col, row};
            scoreTile(position, board);
        }
    }
}



/*
0 0 0 0 0 
0 0 0 0 0 
0 0 0 2 0 
0 0 3 1 5 
0 0 0 4 0 
*/













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
    scoreBoard(board, NULL, NULL);
    
    }


    return 0;
}