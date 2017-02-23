#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QLabel>
#include <QTimer>
#include <QFrame>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QPainter>
#include <QObject>
#include "block.h"
#include "grid.h"



class gameBoard : public QFrame
{
    Q_OBJECT
    
private:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    
    void start();
    int speed();//it will return the falling speed of the blocks.
    void newBlock();//generate new blocks.
    void drawNextBlock();//drawing the next block image, such that it can be passed to mainWindow() to display it.
    void drawBlock(QPainter &painter, int x, int y, int type);//used to draw each small block.
    
    QTimer timer;
    QImage background;
    QPixmap display;
    bool isStarted;
    bool isEnd;
    block curBlock;
    block nextBlock;
    grid *gridBoard;
    int curX;//current x position of the current block.
    int curY;//current y position of the current block.
    int score;
    int level;
    
    static const QColor colorIndex[8];//create a color table, to which drawing could refer.
    
public:
    gameBoard(QWidget *parent = 0);
    virtual ~gameBoard(); //in case it will become a base class.
    

signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void nextBlockImageChanged(QPixmap&);
public slots:
    void updateMovement();//timer would be connected to this function.
    
    };


#endif
