#include <QWidget>
#include <QApplication>
#include <stdlib.h>
#include <QtGui>
#include "mainWindow.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    mainWindow* m = new mainWindow;
    m->show();
    return a.exec();
}
