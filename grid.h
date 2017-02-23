#ifndef GRID_H
#define GRID_H
#include "block.h"


class grid
{
public:
    grid();
    virtual ~grid();//in case it will become a base class.
    int getGrid(int x, int y) {return blockIsFilled[x][y];}
    void clearBoard();
    bool tryMove(const block&, int ,int );
    int removeLines();//here the return value is the gained score atfter removing.
    bool firstTwoRowsOccupied();
    void clearOneLine(int y);
    void shiftAfterRemove(int y);
    void settleDown(block&, int, int);

private:
    int blockIsFilled[10][20];
};

#endif // GRID_H
