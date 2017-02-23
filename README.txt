Project name: Tetris

================================
Author: WANG Juntao
Student ID: 20255651
email: jwangcc@connect.ust.hk

How-to-compile-and-run
================================
>qmake
>make
>./tetris

How-to-play
================================
1. The size of the Game board is 10 square x 20 square. It is empty just before the game start.

2. How to control the blocks.
arrow(up)  Start game (or restart the game.)

arrow(left) -> Move block left

arrow(right) -> Move block right

arrow(down) -> Move block down

Z -> Rotate block in clockwise direction

X -> Rotate block in anti-clockwise direction

3. The stating position of a block center is at the middle of the third top row.

4. When either the top or the second top row of the game board is not empty, or the next block cannot be generated on the game board (when it appears, it would overlap with the background blocks), the game ends.

5. If a row of the game board are completely occupied by the components (squares) of the fixed game boards, the row will disappear, your score will increased and everything above the disappeared row will be shift down. The score would be increased by (10 * combo * combo), where combo equals the number of rows disappeared for a single block.

6. The level will increase by 1 for every 100 scores. The falling speed of the blocks would be  [1000ms - (level -1)*100] per grid square.

Improvement of the demo project
===============================
1. The game can be restarted even if the game is still running.

2. If the newly generated block would overlap with the existence block, it would not be painted.

===============================
Design of the project:
For this game, it mainly contains three parts,
	1. Main window, which displays all the information of this game, including game board, score board, next block display window board.
	2. Game board, which is the active area where main game event happens.
	3. Game logic, which sets up the rules that how the game would be running.
Such that I have separated the UI part (QT part) and the game logic part.

For the main window design is simple, it can be implemented by one mainWindow class (see mainWindow.h and mainWindow.cpp). It is connected to the board class which will emit the current information, including netxt block image, current score, current level.

For the game board, it controls the game flow and image drawing, and it would update the information to the mainWindow class. So I use a board class to implement this (see board.h and board.cpp). It can accept the keyboard input and call some functions from grid class to control the blocks movement. And it use QPainter to draw the background and blocks based on the information in the grid class. Also game board could communicate with the grid class by calling the functions from grid, such that game board would know how the game operate.

For the game logic, it would be a little bit complicated, so I use two classes, block class (see block.h and block.cpp) and grid class (see grid.h and grid.cpp), to implement the logic:

For block class, it contains all the information about the 7 types of block. I used a 8 * 4 * 2 arrays to store all the information. For we have 7 types of block, we use 8 dimensions to indicate 7 types and no types (which implies no block). And every type we have 4 squares, so I use 4 	dimensions to indicate each square. For each square, it has x and y coordinates to indicate its position, so I use 2 dimensions to store x and y coordinates information, furthermore, we set the square that at the center of the big block as (0, 0), such that other 3 squares' coordinates are the relative position about the center block.
And for block class, I also define two methods that can be used to reset the squares coordinates to implement the rotation.

For the grid class, it is the most the important part of the project. In grid class, it contains the information of a 10 * 20 array to store integers. For the game board playing area is 10 squares * 20 squares. So I use this array to represent the coordinate system of the game board, and the integer it stores represents the information of the square at that position, e.g. if there is a square of type 3 big block at position (5, 5), then integer 3 would be stored in array position (5, 5). And if there is no square, then the integer it stored is 0 (which coincides with block class information).
And I also define a function that control the movement of the block, namely, tryMove(const block&, int, int), which take block and new coordinates as arguments, and try if the block with the new coordinates could be fitted into the grid board or not (check if the new position has been occupied by other squares, i.e. if the corresponding array position is stored a non-zero integer), and return the true and false, indicate the trial movement is success or not.
And grid class would also check that if there is any non-zero integer stored in the top two rows. As long as a non-zero integer is detected, function firstRowsOccupied() would return a false value to indicate the game is over.


