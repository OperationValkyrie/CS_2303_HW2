/* Jonathan Chang
 * CS 2303 C01 18
 * Assignment 2 - Game of Life
 * twoD.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "twoD.h"

/**
 * Allocates the memory for a 2D array of characters and returns the array
 * @param rows The number of rows to create in the array
 * @param columns The number of columns to create in the array
 * @return The 2D character array
 */
char** make2Dchar(int rows, int columns) {

	char** grid; // Array of pointers to rows

	grid = (char **) malloc(rows * (sizeof(char *)));
	// Test if failed to allocate
	if(!grid) {
		// If failed to allocate
		return (char **) NULL;
	}
	// Pre-condition: no memory allocated to each row
	for(int i = 0; i < rows; i++) {
		grid[i] = (char *) malloc(columns * (sizeof (char)));
		// Test is failed to allocate
		if(!grid[i]) {
			// If unable to allocate memory
			return (char **) NULL;
		}
	}
	//Post condition: all memory allocated
	grid = clear2Dchar(grid, rows, columns);
	return grid;
}

/**
 * Creates a deep copy of a 2D character array
 * @param original The original array to copy
 * @param rows The number of rows in the original array
 * @param columns The number of columns in the original array
 * @return A deep copy of the original array
 */
char** copy2Dchar(char** original, int rows, int columns) {
	char** copy = make2Dchar(rows, columns);
	// Pre-condition: copy grid is empty
	for(int i = 0; i < rows; i++) {
		// Loop Invariant: 0 < i < rows
		// Pre-condition: row is not yet copied
		for(int j = 0; j < columns; j++) {
			// Loop Invariant 0 < j < columns
			copy[i][j] = original[i][j];
		}
		// Post-condition: row is copied
	}
	// Post-condition: grid is copied
	return copy;
}

/**
 * Fills in an 2D character array with the default value of 'o'
 * @param grid The character array to fill in
 * @param rows The number of rows in the array
 * @param columns The number of columns in the array
 * @return The modified array
 */
char** clear2Dchar(char** grid, int rows, int columns) {
	// Pre-condition: grid not yet filled
	for(int i = 0; i < rows; i++) {
		// Loop Invariant: 0 < i < rows
		// Pre-conditions: rows is not yet filled
		for(int j = 0; j < columns; j++) {
			// Loop Invariant: 0 < j < columns
			grid[i][j] = 'o';
		}
		// Post-condition: row is filled
	}
	// Post-condition: column is filled
	return grid;
}

/**
 * Prints out the given 2D character array
 * @param grid The character array
 * @param rows The number of rows in the grid
 * @param columns The number of columns in the grid
 * @return void
 */
void print2Dchar(char** grid, int rows, int columns) {
	// Pre-condition: grid has not been printed yet
	for(int i = 0; i < rows; i++) {
		// Loop Invariant: 0 < i < rows
		// Pre-condition: row has not been printed yet
		for(int j = 0; j < columns; j++) {
			// Loop Invariant: 0 < j < columns
			// Test if cell is alive
			if(grid[i][j] == 'x') {
				// If cell is alive
				printf("%c", grid[i][j]);
			} else {
				// If cell is dead
				printf(" ");
			}
		}
		// Post-condition: row has been printed
		printf("\n");
	}
	//Post-condition: grid has been printed
}

/**
 * Compares two 2D character arrays and test if they are equal
 * @param grid1 The first array to compare
 * @param grid2 The second array to compate
 * @param rows The number of rows in both arrays
 * @param columns The number of columns in both arrays
 * @return Whether the two arrays were equal (1 for equal, 0 for not equal)
 */
int equal2Dchar(char** grid1, char** grid2, int rows, int columns) {
	// Pre-condition: No cells checked yet
	for(int i = 0; i < rows; i++) {
		// Loop Invariant: 0 < i < rows
		// Pre-condition: No cell in row checked yet
		for(int j = 0; j < columns; j++) {
			// Loop Invariant: 0 < j < columns
			// Test if cells are the same
			if(grid1[i][j] != grid2[i][j]) {
				// If cells are different
				return 0;
			}
		}
		//Post-condition: Row has been checked
	}
	// Post-condition: Grid has been checked
	return 1;
}

/**
 * Reads a 2D character array from a given text file and puts it into the given
 * array
 * @param file The text file to read from
 * @param rows The amount of rows in the array
 * @param columns The amount of columns in the array
 * @return The array with the contents overwritten
 */
char** read2Dchar(FILE *file, int rows, int columns) {
	char line[columns]; // Holds the character array of each line
	int i = 0; // Holds the current row number
	int maxColumn = 0;
	char** grid = make2Dchar(rows, columns);

	// Pre-conditions: fscanf current at top of file
	// While there are still lines and current line is less than or equal to
	// the number of rows
	while(fscanf(file, "%s", line) != EOF && i < rows) {
		// Loop Invariant: 0 < i < rows
		// Pre-condition: Line not yet read
		for(int j = 0; line[j] != '\0' && j < columns; j++) {
			// Loop Invariant 0 < j < columns
			grid[i][j] = line[j];
			// Test if j is greater than maxColumn
			if(j > maxColumn) {
				// If J is greater than maxColumn
				maxColumn = j;
			}
		}
		// Post-condition: Line is read
		i++;
	}
	int maxRows = i; // Holds the height of the input
	maxColumn++;

	// maxRows now holds number of lines and maxColumn the width of the input

	// Shift to center
	char** gridShift = make2Dchar(rows, columns);
	int xShift = floor((columns - maxColumn) / 2);
	int yShift = floor((rows - maxRows) / 2);

	// Pre-condition: No cells copied over to new grid
	for(int i = 0; i < maxRows; i++) {
		// Loop Invariant: 0 < i < maxRows
		// Pre-condition: No cells copied over in this row
		for(int j = 0; j < maxColumn; j++) {
			// Loop Invariant: 0 < j < maxColumns
			gridShift[i + yShift][j + xShift] = grid[i][j];
		}
		//Post-condition: All cells from row copied over
	}
	// Post-condition: all cells copied over ot center of gridShift

	free2Dchar(grid, rows);

	return gridShift;
}

/**
 * Frees up the memory of a given 2D character array
 * @param grid The character array to free
 * @param rows The number of rows in the array
 * @return void
 */
void free2Dchar(char** grid, int rows) {
	// Pre-condition: No rows freed yet
	for(int i = 0; i < rows; i++) {
		// Loop Invariant: 0 < i < rows
		free(grid[i]);
	}
	// Post-condition: All rows freed
	free(grid);
}
