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
            if (tilepos[1] > 0) {
                return board[tilepos[0]][tilepos[1] - 1];
            } else {
                return -1;
            }
            break;
        case DOWN:
            if (tilepos[1] < 4) {
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

int checkForChurch(int xoffset, int yoffset, int board[5][5]) {
    if (!((xoffset < 0) || (xoffset > 4) || (yoffset < 0) || (yoffset > 4)) && (board[xoffset][yoffset] == 3)) {
        return 2;
    }
    else {
        return 0;
    }
    
}
//note - scoreport's first run is on the port itself, it then moves to water. This means it returns 1 more point than necessary, shaved off in scoreTile().
int scorePort(int portpos[2], int board[5][5], int visited[24][2], int* visitedmax, int *sumpoints) { 
    int isTileVisited = 0;
    //loop through the tiles visited to see if this tile is included.
    for (int visitcheck = 0; visitcheck < *visitedmax; visitcheck++) {

        if ((visited[visitcheck][0] == portpos[0]) && (visited[visitcheck][1] == portpos[1])) { 
            isTileVisited = 1;
        }
    }

    if (isTileVisited == 0) {
        //Since the water has not been visited, we first add it to the array (updating length of search check), then we can score it
        visited[*visitedmax][0] = portpos[0];
        visited[*visitedmax][1] = portpos[1];
        (*visitedmax)++;
        (*sumpoints)++;
        
        //now we check if adjacent water tiles can score

        if (getTileInDirection(UP, portpos, board) == 1) {
            portpos[1]--;
            scorePort(portpos, board, visited, visitedmax, sumpoints);
            portpos[1]++;
            
        }
        if (getTileInDirection(DOWN, portpos, board) == 1) {
            portpos[1]++;
            scorePort(portpos, board, visited, visitedmax, sumpoints);
            portpos[1]--;
            
        }
        if (getTileInDirection(LEFT, portpos, board) == 1) {
            portpos[0]--;
            scorePort(portpos, board, visited, visitedmax, sumpoints);
            portpos[0]++;
            
        }
        if (getTileInDirection(RIGHT, portpos, board) == 1) {
            portpos[0]++;
            scorePort(portpos, board, visited, visitedmax, sumpoints);
            portpos[0]--;
            
        }
    }   
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
            int portpos[2] = {tilepos[0], tilepos[1]};
            scorePort(portpos, board, visitedwater, &visitedmax, &tilescore);
            tilescore--; //remove the initial point that was added for the tile itself, since we only want to score the water connected to it.
            break;
            
        case 3:
            tilescore = 8;  
            //as a possible strat, we could stop from checking the rest of the churches if already less than 1. 
            //However overhead from checking points = to 1 might be too much for these rare scenarios.
            tilescore -= checkForChurch(tilepos[0] - 1, tilepos[1], board);
            tilescore -= checkForChurch(tilepos[0] - 2, tilepos[1], board);
            tilescore -= checkForChurch(tilepos[0] - 1, tilepos[1] - 1, board);
            tilescore -= checkForChurch(tilepos[0], tilepos[1] - 2, board);
            tilescore -= checkForChurch(tilepos[0] + 1, tilepos[1] - 1, board);
            tilescore -= checkForChurch(tilepos[0] + 2, tilepos[1], board);
            tilescore -= checkForChurch(tilepos[0] + 1, tilepos[1] + 1, board);
            tilescore -= checkForChurch(tilepos[0], tilepos[1] + 2, board);
            tilescore -= checkForChurch(tilepos[0] - 1, tilepos[1] + 1, board);
            tilescore -= checkForChurch(tilepos[0], tilepos[1] - 1, board);
            tilescore -= checkForChurch(tilepos[0], tilepos[1] + 1, board);
            tilescore -= checkForChurch(tilepos[0] + 1, tilepos[1], board);

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
        printf("\nYou have %d points and have %d turn(s) remaining.\n\n", score, turn);

        takeManualInput(locationtoplaceman, tiletoplaceman); //temporary until AI is implemented, this will take manual input for tile placement

        placeTile(locationtoplaceman, tiletoplaceman, board, cornboard, turn); 
        
        printf("Placed tile in slot %d, %d \n", locationtoplaceman[0], locationtoplaceman[1]); //also will be removed with location/tiletoplaceman
        
        scoreBoard(board, &score, pointsboard, cornboard);

        printBoard(board, pointsboard);
    }
    printf("Game over! You reached %d points!", score);

    return 0;
}