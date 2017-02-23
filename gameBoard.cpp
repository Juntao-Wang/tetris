#include <QWidget>
#include "gameBoard.h"

//set some constants to make the code more readable.
//the width and height of the board are 10 and 20 squares respectively.
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
//for each square, it has 20 pixes in length.
#define DISTANCE 20


const QColor gameBoard::colorIndex[8] = {//each type of block has their own color.
    Qt::transparent, Qt::yellow, Qt::blue, Qt::red, Qt::magenta, Qt::green, Qt::cyan, Qt::gray
};

gameBoard::gameBoard(QWidget *parent) : QFrame(parent){
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    isStarted = true;
    isEnd = false;
    score = 0;
    level = 1;
    background.load("background.bmp");//load the background image, so we can draw it.
    setFixedSize(BOARD_WIDTH * DISTANCE, BOARD_HEIGHT * DISTANCE);
    gridBoard = new grid();//initialize the grid object.
    display = QPixmap(100, 140);//initialize the background image of the next block.
    curBlock.setNull();//clean up current block.
    nextBlock.randomType();//prepare the nextblock.
    setFocusPolicy(Qt::StrongFocus);//make key enter can be accepted.
    connect(&timer,SIGNAL(timeout()), this, SLOT(updateMovement()));//connect the timer to the unpdateMovement(), such that after each timeout interval, it would do something.
}

gameBoard::~gameBoard(){//free the space.
    delete gridBoard;
}

void gameBoard::start(){
    gridBoard->clearBoard();
    curBlock.setNull();//clean up the current block.
    repaint();
    isStarted = true;
    isEnd = false;
    score = 0;
    level = 1;
    emit scoreChanged(score);
    emit levelChanged(level);
    newBlock();//for new game start, generate new block.
    timer.start(speed());//start timing.
}

void gameBoard::keyPressEvent(QKeyEvent *event){
    if(!isStarted) {
        if(event->key() == Qt::Key_Up){//if the game is not started, it can only accept the start key. i.e. Up.
            start();
        }else{
            return;
        }
    }
    
    switch (event->key()) {
        case Qt::Key_Up:
            start();
            break;
        case Qt::Key_Left:
            if(gridBoard->tryMove(curBlock, curX - 1, curY)){
                curX --;//if can move, then change the coordinates of the center of the block.
                repaint();
            }

            break;
        case Qt::Key_Right:
             if(gridBoard->tryMove(curBlock, curX + 1, curY)){
                 curX ++;//if can move, then change the coordinates of the center of the block.
                 repaint();
             }
            break;
        case Qt::Key_Down:
             if(gridBoard->tryMove(curBlock, curX , curY + 1)){
                 curY ++;//if can move, then change the coordinates of the center of the block.
                 repaint();
             }
            break;
        case Qt::Key_Z:
             if(gridBoard->tryMove(curBlock.rotateClock(), curX , curY)){//if can rotate.
                 curBlock = curBlock.rotateClock();//change the rotated block to current block.
                 repaint();
             }
            break;
        case Qt::Key_X:
             if(gridBoard->tryMove(curBlock.rotateCounter(), curX , curY)){//if can rotate.
                 curBlock = curBlock.rotateCounter();//change the rotated block to current block.
                 repaint();
             }
            break;
        default:
            event->ignore();//if the key event is none of above, then igore.
    }
    
}

void gameBoard::paintEvent(QPaintEvent *){//when repaint() is called.
    QPainter painter(this);
    
    painter.drawPixmap(0, 0, QPixmap::fromImage(background));//draw the background.
    for(int i = 0; i !=BOARD_WIDTH; ++i){//draw the settled blocks. (background blocks.)
        for (int j = 0; j != BOARD_HEIGHT; ++j){
            drawBlock(painter, i , j, gridBoard->getGrid(i,j));//draw the small block according to the grid information.
        }
    }
    
    if(curBlock.type() != 0){//draw the block that is still moving.
        for (int i =0; i !=4; ++i){
            drawBlock(painter, curX + curBlock.x(i), curY + curBlock.y(i), curBlock.type());
        }
    }
    
}

void gameBoard::updateMovement(){//when timeout, this function would be called.
    //each timeout interval, the block would drop down one line.
    if(gridBoard->tryMove(curBlock,curX, curY +1)){
        curY ++;
    }else{//if it cannot drop down.
        gridBoard->settleDown(curBlock, curX, curY);//we settle it into the background. Within the settleDown function, we would also check if it has completed rows.
        //and this function will return the scores that gained by eliminating row.
        score += gridBoard->removeLines();//check if it has completed rows.
        level = score/100 +1;
        if(level >10){//max level is 10.
            level = 10;
        }
        emit scoreChanged(score);
        emit levelChanged(level);
        isEnd = gridBoard->firstTwoRowsOccupied();//if first two rows has small block, then the game is over.
        newBlock();//generate new block. And newBlock() will check whether this new block can be generated on the game board.
        if(isEnd) {//if first two rows have been occupied or the new block cannot be generated, then game over.
            timer.stop();//if the game is ended, stop the timer.
            curBlock.setNull();//if the game is ended, clean up the trial generated current block.
            return;
        }
        timer.start(speed());//reset the speed of the game.
    }
    repaint();
}


int gameBoard::speed(){//this is the timeout interval, controlling the falling speed.
    return (1000 - (level-1)*100);//unit is millisecond per square grid.
}


void gameBoard::newBlock(){
    curBlock = nextBlock;
    curX = BOARD_WIDTH/2;//starting x position is at the middle.
    curY = 2;
    if(!gridBoard->tryMove(curBlock, curX, curY)){//if new block cannot be generated, then stop.
        isEnd = true;
        isStarted = false;
    }else{//if it still can generated, we continue, and draw it out.
        nextBlock.randomType();
        drawNextBlock();
        repaint();
    }
}

void gameBoard::drawBlock(QPainter &painter, int x, int y, int type){
    QColor color = colorIndex[type];//get the color.
    
    painter.fillRect(x * DISTANCE, y * DISTANCE, DISTANCE, DISTANCE, color);//fill the color in the small block.
    if(type != 0){//draw the black lines around the small block.
        painter.drawRect(x * DISTANCE, y * DISTANCE, DISTANCE, DISTANCE);
    }
}

void gameBoard::drawNextBlock(){//for the next block displaying, we use a 100 x 140 pixmap as background, it is big enough to display any type of block.
    //we use all white background as our canvas.
    display.fill();
    QPainter painter(&display);
    for (int i =0; i !=4; ++i){
        //in the display window, we set the center of the block at the position (2, 3)
        //and we call draw block to draw it.
        drawBlock(painter, 2 + nextBlock.x(i), 3 + nextBlock.y(i), nextBlock.type());
    }
    emit nextBlockImageChanged(display);//emit the image, let the mainWindow know, and update the image.
    
}




