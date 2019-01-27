/* Jonathan Chang
 * CS 2303 C01 18
 * Assignment 2 - Game of Life
 * twoD.h
 */


#ifndef TWOD_H_
#define TWOD_H_

// Function prototypes:
char** make2Dchar(int rows, int columns);
char** copy2Dchar(char** original, int rows, int columns);
char** clear2Dchar(char** grid, int rows, int columns);
void print2Dchar(char** grid, int rows, int columns);
int equal2Dchar(char** grid1, char** grid2, int rows, int columns);
char** read2Dchar(FILE *file, int rows, int columns);
void free2Dchar(char** grid, int rows);

char** createGen(char** grid, int rows, int columns);
int getNeighbors(char** grid, int x, int y, int rows, int columns);
int stuckGrids(char** gridOld, char** gridCurrent, char** gridFuture, int rows, int columns);
int hasAlive(char** grid, int rows, int columns);


#endif /* 2D_H_ */
