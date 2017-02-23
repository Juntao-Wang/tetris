#include "grid.h"

//set some constants to make the code more readable.
//the width and height of the board are 10 and 20 squares respectively.
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
//for each square, it has 20 pixes in length.
#define DISTANCE 20


grid::grid(){
    clearBoard();
}

grid::~grid(){//for no pointer has been newed, do nothing.

}

void grid::clearBoard(){//clear board, set all the element in the array to be 0. (0 indicate the no type, equivalent to no block.)
    for (int i =0; i !=10; ++i){
        for (int j = 0; j != 20; ++j){
            blockIsFilled[i][j] = 0;
        }
    }
}

int grid::removeLines(){//this will return the scores by removing the lines.
    int combo = 0;//count how many rows would be removed in one time.
    for (int j = 0; j != BOARD_HEIGHT; ++j){//check each row.
        for (int i = 0; i != BOARD_WIDTH; ++i){
            if(blockIsFilled[i][j] == 0){//if a row has empty space, break to check other rows.
                break;
            }
            if(i == BOARD_WIDTH - 1){//if a row from starting position to the end position has no empty space. Then we would remove it.
                combo++;
                clearOneLine(j);
                shiftAfterRemove(j);
            }
        }
    }
    return 10* combo * combo;
}

void grid::shiftAfterRemove(int y){
    //after clear one line, all the blocks on top of that line would be shifted down one line.
    for (int j = y; j != 0; --j){
        for (int i = 0; i != BOARD_WIDTH; ++i){
            blockIsFilled[i][j] = blockIsFilled[i][j - 1];
        }
    }
}

void grid::clearOneLine(int y){
    for (int x = 0; x != BOARD_WIDTH; ++x){
        blockIsFilled[x][y] = 0;
    }
}

bool grid::tryMove(const block& newBlock, int newX, int newY){
    if (newBlock.type() == 0) return false;//if there is no block.
    for(int i = 0; i !=4; ++i){//check each small block.
        int x = newX + newBlock.x(i);
        int y = newY + newBlock.y(i);
        if (x < 0 ||
            x >= BOARD_WIDTH ||
            y >= BOARD_HEIGHT){//if the block tends to cross the boundaries, it would fail.
            return false;
        }
        if (y>=0 && blockIsFilled[x][y] != 0){//within the playing area, if the position the block try to move has been occupied, if would fail.
            return false;
        }
    }
    //if it can move.
    return true;
}

void grid::settleDown(block &B, int x, int y){//we put the small block information into the grid array. Such that, gameBoard could draw the blocks based on this array.
    for (int i = 0; i != 4; ++i){
        int blockX = x + B.x(i);
        int blockY = y + B.y(i);
        if(blockY >= 0) blockIsFilled[blockX][blockY] = B.type();
    }
}

bool grid::firstTwoRowsOccupied(){//check first two tows.
    for (int j = 0; j !=2; ++j){
        for (int i = 0; i != 10; ++i){
            if(blockIsFilled[i][j] != 0){//if any grid in the first two has been occupied, then return true.
                return true;
            }
        }
    }
    return false;//if no grid has been occupied, return false.
}

