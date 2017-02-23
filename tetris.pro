HEADERS = block.h \
	gameBoard.h \
	mainWindow.h \
    grid.h
SOURCES = main.cpp \
	block.cpp\
	gameBoard.cpp\
	mainWindow.cpp \
    grid.cpp

greaterThan(QT_MAJOR_VERSION, 4):QT += widgets
