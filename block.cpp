#include <QtCore>
#include <stdlib.h>
#include <QDebug>
#include "block.h"

//table of the types.
const int block::coordsTable[8][4][2] = {
    { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },//no type
    { { 0, 1 },  { 0, 0 },   { 1, 0 },  { 1, -1 } },
    { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
    { { 0, 1 },  { 0, 0 },   { 0, -1 },   { 0, -2 } },
    { { 1, 0 },  { 0, 0 },   { -1, 0 },   { 0, -1 } },
    { { 0, 0 },   { -1, 0 },   { 0, 1 },   { -1, 1 } },
    { { 1, 1 }, { 0, 1 },  { 0, 0 },   { 0, -1 } },
    { { -1, 1 },  { 0, 1 },  { 0, 0 },   { 0, -1 } }
};


block::block(){
    blockType = 0;
}

block::~block(){//for no pointer has been newed, do nothing.

}

void block::randomType(){
    blockType = rand() % 7 + 1;
    for (int i = 0; i < 4 ; ++i) {
        for (int j = 0; j < 2; ++j)
            coords[i][j] = coordsTable[blockType][i][j];
    }
}

void block::setNull(){
    blockType = 0;
}

block block::rotateCounter(){
    //for this is used for tryMove, we first only generate a mirror of the block after rotation. But not real rotate it.
    block afterRotate = *this;
    for(int i = 0;i < 4; ++i){
        int curX = x(i);
        int curY = y(i);
        afterRotate.setX(i, curY);
        afterRotate.setY(i, -curX);
    }
    
    return afterRotate;
}

block block::rotateClock(){
    //for this is used for tryMove, we first only generate a mirror of the block after rotation. But not real rotate it.
    block afterRotate = *this;
    for(int i = 0;i < 4; ++i){
        int curX = this->x(i);
        int curY = this->y(i);
        afterRotate.setX(i, -curY);
        afterRotate.setY(i, curX);
    }
    return afterRotate;
}

