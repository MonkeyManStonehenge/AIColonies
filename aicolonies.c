#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};


    
void printBoard(int board[5][5], int pointboard[5][5]) {
    printf("\n");
    for (int col = 0; col <= 4; col++) {
        for (int row = 0; row <= 4; row++) {
            printf("%d(%d) ", board[row][col], pointboard[row][col]);
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
    int isTileVisited = 0;
    for (int visitcheck = 0; visitcheck < *visitedmax; visitcheck++) {
        if ((visited[visitcheck][0] == portpos[0]) && (visited[visitcheck][1] == portpos[1])) { //loop through the tiles visited to see if this tile is included.
            isTileVisited = 1;
        }
    }
    if (isTileVisited == 0) {
        //Since the water has not been visited, we first add it to the array, then we can score it
        printf("unvisited water at %d, %d\n", portpos[0], portpos[1]);
        printf("visited is previously %d long, and sumpoints is now %d\n", *visitedmax, *sumpoints);
        (*visitedmax)++;
        visited[*visitedmax][0] = portpos[0];
        visited[*visitedmax][1] = portpos[1];
        (*sumpoints)++;
        printf("visited is now %d long, and sumpoints is now %d\n", *visitedmax, *sumpoints);
        
        

        if (getTileInDirection(UP, portpos, board) == 1) {
            int newportpos[2] = {portpos[0], portpos[1] - 1};
            scorePort(newportpos, board, visited, visitedmax, sumpoints);
            printf("attempting to score up now.\n");
        }
        if (getTileInDirection(DOWN, portpos, board) == 1) {
            int newportpos[2] = {portpos[0], portpos[1] + 1};
            scorePort(newportpos, board, visited, visitedmax, sumpoints);
            printf("attempting to score down now.\n");
        }
        if (getTileInDirection(LEFT, portpos, board) == 1) {
            int newportpos[2] = {portpos[0] - 1, portpos[1]};
            scorePort(newportpos, board, visited, visitedmax, sumpoints);
            printf("attempting to score left now.\n");
        }
        if (getTileInDirection(RIGHT, portpos, board) == 1) {
            int newportpos[2] = {portpos[0] + 1, portpos[1]};
            scorePort(newportpos, board, visited, visitedmax, sumpoints);
            printf("attempting to score right now.\n");
        }

    }
    else {printf("water has already been visited");}
        
}
    


void placeTile(int tilepos[2], int tileID, int board[5][5], int cornboard[5][5], int turn) {
    if (tileID == 5) {
        cornboard[tilepos[0]][tilepos[1]] = (turn / 3) + 1; //Note that this is integer division, it's intended to round down to the nearest whole number
    }
    board[tilepos[0]][tilepos[1]] = tileID;
}

int scoreTile(int tilepos[2], int board[5][5], int cornboardval) {
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
        
        
            int visitedwater[24][2] = {{0, 0}};
            int visitedmax = 0;

            scorePort(tilepos, board, visitedwater, &visitedmax, &tilescore);
            tilescore--; //remove the initial point that was added for the tile itself, since we only want to score the water connected to it.
            break;
            
        case 3:
            tilescore = 8;
            int checkpos[2] = {tilepos[0], tilepos[1]};
            if (tilepos[1] < 4) { //UP CHECKING
                checkpos[1]++;
                if (getTileInDirection(UP, checkpos, board) == 3) {
                    tilescore-=2;
                }
                checkpos[1] = tilepos[1];
                checkpos[0]++;
                if (getTileInDirection(RIGHT, checkpos, board) == 3) {
                    tilescore-=2;
                }
                checkpos[0] -=2;
                if (getTileInDirection(LEFT, checkpos, board) == 3) {
                    tilescore-=2;
                }
                if (board[tilepos[0]][tilepos[1] + 1] == 3) {
                    tilescore-=2;
                }
            }
            if (tilepos[1] > 0) { //DOWN CHECKING
                checkpos[1]--;
                if (getTileInDirection(DOWN, checkpos, board) == 3) {
                    tilescore-=2;
                }
                checkpos[1] = tilepos[1];
                checkpos[0]++;
                if (getTileInDirection(RIGHT, checkpos, board) == 3) {
                    tilescore-=2;
                }
                checkpos[0] -=2;
                if (getTileInDirection(LEFT, checkpos, board) == 3) {
                    tilescore-=2;
                }
                if (board[tilepos[0]][tilepos[1] - 1] == 3) {
                    tilescore-=2;
                }
            }
            if (tilepos[0] < 4) { //RIGHT CHECKING
                if (board[tilepos[0] + 1][tilepos[1]] == 3) {
                    tilescore-=2;
                }
                checkpos[0]++;
                if (getTileInDirection(RIGHT, checkpos, board) == 3) {
                    tilescore-=2;
                }
            }
            if (tilepos[0] > 0) { //LEFT CHECKING
                if (board[tilepos[0] - 1][tilepos[1]] == 3) {
                    tilescore-=2;
                }
                checkpos[0]--;
                if (getTileInDirection(LEFT, checkpos, board) == 3) {
                    tilescore-=2;
                }
            }

            if (tilescore < 1) {
                tilescore = 1;
            }
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
            tilescore = cornboardval;
            break;
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

void scoreBoard(int board[5][5], int *score, int pointboard[5][5], int cornboard[5][5]) {
    *score = 0;
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            int position[] = {col, row};
            int newpoints = scoreTile(position, board, cornboard[col][row]);
            *score += newpoints;
            if (pointboard != NULL) {
                pointboard[col][row] = newpoints;
            }
        } 
    }
}



int main() {

    srand(time(NULL));
    int board[5][5] = {0};
    int cornboard[5][5] = {0};
    int locationtoplaceman[2] = {0, 0};
    int tiletoplaceman;
    int pointsboard[5][5] = {0};
    int score = 0;


    for (int turn = 25; turn > 0; turn--) {
    tiletoplaceman = (rand() % 6) + 1; //randomize next tile to place
    printf("\nYou have %d points but have %d turn(s) remaining.\n\n", score, turn);

    takeManualInput(locationtoplaceman, tiletoplaceman); //temporary until AI is implemented, this will take manual input for tile placement

    placeTile(locationtoplaceman, tiletoplaceman, board, cornboard, turn); 
    
    printf("Placed tile in slot %d, %d \n", locationtoplaceman[0], locationtoplaceman[1]); //also will be removed with location/tiletoplaceman
    
    scoreBoard(board, &score, pointsboard, cornboard);

    printBoard(board, pointsboard);
    
    }


    return 0;
}