#ifndef BLOCK_H
#define BLOCK_H


class block{
private:
    //set up the block type table.
    static const int coordsTable[8][4][2];
    
    int blockType;
    //we have four rectangles, and each rectangle has x and y position labeling.
    int coords[4][2];
    //setX and setY can be used by the rotation method to change the position of each small block.
    void setX(int index, int x) { coords[index][0] = x ; }
    void setY(int index, int y) { coords[index][1] = y ; }
    
public:
    block();
    virtual ~block();//in case it will become a base class.
    //used to set up the random type of the next block.
    void randomType();
    //clean up the block.
    void setNull();
    int x(int index) const { return coords[index][0]; }
    int y(int index) const { return coords[index][1]; }
    int type() const {return blockType;}
    block rotateCounter();
    block rotateClock();
};

#endif
