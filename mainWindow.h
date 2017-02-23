#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>
#include <QFrame>
#include <QWidget>
#include <QLabel>
#include <QObject>
#include "gameBoard.h"
class mainWindow : public QWidget
{
    Q_OBJECT
    
public:
    mainWindow();
    virtual ~mainWindow();//in case it will become a base class.

    
private:
    
    gameBoard *board;
    QLabel *nextBlockLabel;
    QLabel *scoreLabel;
    QLabel *levelLabel;
    
public slots:
    void scoreDisplay(int score);
    void levelDisplay(int level);
    void nextBlockDisplay(QPixmap&);
    
};

#endif
