#include "mainWindow.h"
mainWindow::mainWindow(){
    board = new gameBoard();
    scoreLabel = new QLabel("score: 0");
    levelLabel = new QLabel("level: 0");
    nextBlockLabel = new QLabel();
    //setup initial display window image.
    QPixmap pix;
    pix = QPixmap(100, 140);
    pix.fill();
    nextBlockLabel->setPixmap(pix);
    QGridLayout *mainLayout = new QGridLayout(this);
    //set up the position for different widgets.
    mainLayout->addWidget(board, 0 ,0, 20,1);
    mainLayout->addWidget(scoreLabel,17,1);
    mainLayout->addWidget(levelLabel,16,1);
    mainLayout->addWidget(nextBlockLabel, 8, 1);
    setLayout(mainLayout);
    connect(board, SIGNAL(scoreChanged(int)), this, SLOT(scoreDisplay(int)));
    connect(board, SIGNAL(levelChanged(int)), this, SLOT(levelDisplay(int)));
    connect(board, SIGNAL(nextBlockImageChanged(QPixmap&)), this, SLOT(nextBlockDisplay(QPixmap&)));
    
}

mainWindow::~mainWindow(){//destruct those have been newed.
    delete board;
    delete scoreLabel;
    delete levelLabel;
    delete nextBlockLabel;
}

void mainWindow::scoreDisplay(int score){
    scoreLabel->setText("score: "+ QString::number(score));
    
}

void mainWindow::levelDisplay(int level){
    levelLabel->setText("level: "+ QString::number(level));
    
}

void mainWindow::nextBlockDisplay(QPixmap& image){
    nextBlockLabel->setPixmap(image);
}

