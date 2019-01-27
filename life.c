/* Jonathan Chang
 * CS 2303 C01 18
 * Assignment 2 - Game of Life
 * life.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "twoD.h"

/** Main function.
 * @param argc Number of words on the command line.
 * @param argv Array of pointers to character strings containing the
 *    words on the command line.
 * @return 0 if success, 1 if invalid command line or unable to open file.
 *
 */
int main(int argc, char **argv) {
	printf("Game of Life\n");

	char *inputFileName; // Name of file containing initial grid
	FILE *input; // Stream descriptor for file containing initial grid
	int rows; // Number of rows in the grid
	int columns; // Number of columns in the grid
	int gens; // Number of generations to produce
	int ifPrint; // 1 if user wants to print each generation, 0 if not
	int ifPause; // 1 if user wants to pause after each generation, 0 if not
	char **gridOld; // A 2D array to hold the previous pattern
	char **gridCurrent; // A 2D array to hold the current generation
	char **gridFuture; // A 2D array to hold the future generation

	// See if there are the right number of arguments on the command line
	if ((argc < 5) || (argc > 7)) {
		// If not, tell the user what to enter.
		printf("Usage:\n");
		printf("This program requires the following arguments:\n");
		printf("(int) The width of the desired grid.\n");
		printf("(int) The height of the desired grid\n");
		printf("(int) The number of desired generations.\n");
		printf("(String) The name of the text file to read from.\n");
		printf("(char) (optional) Whether to print out each generation (y/n)\n");
		printf("(char) (optional) Whether to pause between generations (y/n)\n");
		printf("  ./life rows columns generations inputFile [print] [pause]\n");
		return EXIT_FAILURE;
	}

	// Read the mandatory inputs from the arguments
	columns = atoi(argv[1]);
	rows = atoi(argv[2]);
	gens = atoi(argv[3]);
	inputFileName = argv[4];

	// Test if valid generations number
	if(gens <= 0) {
		// If invalid generations number
		printf("The number of generations must be greater than 0.\n");
		return EXIT_FAILURE;
	}

	// Set optional variables
	ifPrint = 0;
	ifPause = 0;
	switch(argc) {
		case 7:
			// Test if first letter is y
			if(argv[6][0] == 'y') {
				// If first letter is y
				ifPause = 1;
			}
			// Test if first letter is y
			if(argv[5][0] == 'y') {
				// If first letter is y
				ifPrint = 1;
			}
			break;
		case 6:
			// Test if first letter is y
			if(argv[5][0] == 'y') {
				// If first letter is y
				ifPrint = 1;
			}
			break;
	}

	// Open file given in command line
	input = fopen(inputFileName, "r");
	// Test if unable to open file
	if (!input) {
		// If unable to open file
		printf("Unable to open input file: %s\n", inputFileName);
		return EXIT_FAILURE;
	}

	// Allocate memory for gridCurrent and read from the input file
	gridOld = make2Dchar(rows, columns);
	gridCurrent = read2Dchar(input, rows, columns);
	// gridFuture is allocated for each generation
	if(!gridCurrent) {
		printf("Unable to allocate memory.");
		return EXIT_FAILURE;
	}

	int genNumber = 0; // Holds the current generation number
	int stuck = 0; // Holds whether the grid is stuck (1 if stuck, 0 if not)

	// Pre-condition: no generations generated yet
	while(genNumber < gens && hasAlive(gridCurrent, rows, columns) && !stuck) {
		// Loop Invariant: genNumber < gen && cells alive && new patterns
		// Test if option to print
		if(ifPrint) {
			// If option is to print
			printf("\nGeneration: %d\n", genNumber);
			print2Dchar(gridCurrent, rows, columns);
		}
		gridFuture = createGen(gridCurrent, rows, columns);
		// Test if unable to allocate memory
		if(!gridFuture) {
			printf("Unable to allocate memory.");
			return EXIT_FAILURE;
		}

		stuck = stuckGrids(gridOld, gridCurrent, gridFuture, rows, columns);

		free2Dchar(gridOld, rows);
		gridOld = gridCurrent;
		gridCurrent = gridFuture;

		genNumber++;
		if(ifPause) {
			getchar();
		}
	}
	// Post condition: Reach end condition
	//	Generation number reached
	//	All cells died
	//	Pattern became stationary
	//	Pattern became alternating

	printf("\nFinal Generation:%d\n", genNumber);
	print2Dchar(gridCurrent, rows, columns);
	printf("Final Generation:%d\n", genNumber);
	printf("\n");

	// Test if any alive cells
	if(!hasAlive(gridCurrent, rows, columns)) {
		// If no alive cells
		printf("Terminated: All cells are dead.\n");
	// Test if generation is stuck
	} else if(stuck) {
		// If generation is stuck
		printf("Terminated: Stuck or alternating grid patterns.\n");
	} else {
		// If neither stuck nor all cells dead
		printf("Terminated: Generation number reached.\n");
	}
	return EXIT_SUCCESS;
}

/**
 * Creates a new generation based on the given grid
 * @param grid A 2D character array to make a new generation from
 * @param rows The number of rows in the array
 * @param columns The number of columns in the array
 * @return A new grid that holds the new generation
 */
char** createGen(char** grid, int rows, int columns) {
	char** gridFuture = make2Dchar(rows, columns);
	// Pre-condition: gridFuture has not been generated
	for(int i = 0; i < rows; i++) {
		// Loop Invariant: 0 < i < rows
		// Pre condition: row has not been generated
		for(int j = 0; j < columns; j++) {
			// Loop Invariant: 0 < j < columns
			int neighbors = getNeighbors(grid, i, j, rows, columns);
			// Test if cell is alive
			if(grid[i][j] == 'x') {
				// If cell is alive
				// Test if cell has too many or too few neighbors
				if(neighbors < 2 || neighbors > 3) {
					// If cell has too many or too few neighbors
					gridFuture[i][j] = 'o';
				} else {
					// If number of neighbors is 2 or 3
					gridFuture[i][j] = 'x';
				}
			} else {
				// If cell is dead
				// Test if number of neighbors is 3
				if(neighbors == 3) {
					// If number of neighbors is 3
					gridFuture[i][j] = 'x';
				} else {
					// If number of neighbors is any other number
					gridFuture[i][j] = 'o';
				}
			}
		}
	}
	return gridFuture;
}

/**
 * Gets the number of alive neighbors that a cell has
 * @param grid The grid to reference
 * @param y The y coordinate of the cell
 * @param x The x coordinate of the cell
 * @param rows The number of rows in the grid
 * @param columns The number of columns in the grid
 * @return The number of alive neighbors the cells has
 */
int getNeighbors(char** grid, int y, int x, int rows, int columns) {
	int neighbors = 0;

	// Get number of top neighbors
	// Test if cell is on top row
	if(y != 0) {
		// If cell is not on top row
		int start = x - 1;
		int end = x + 1;
		// Test if cell is on first column
		if(x == 0) {
			start = x;
		}
		// Test if cell is on last column
		if(x == columns) {
			end = x;
		}
		// Pre-condition: Top three cells have not been counted
		for(int i = start; i <= end; i++) {
			// Loop Invariant: start < i < end
			// Test if cell is alive
			if(grid[y - 1][i] == 'x') {
				// If cell is alive
				neighbors++;
			}
		}
		//Post-condition: Top three cells have been counted
	}

	// Get number of bottom neighbors
	// Test if cell is on last row
	if(y != rows - 1) {
		// If cell is not on last row
		int start = x - 1;
		int end = x + 1;
		// Test if cell is on first column
		if(x == 0) {
			start = x;
		}
		// Test if cell is on last column
		if(x == columns) {
			end = x;
		}
		// Pre-condition: Bottom three cells have not been counted
		for(int i = start; i <= end; i++) {
			// Loop Invariant: start < i < end
			// Test if the cell is alive
			if(grid[y + 1][i] == 'x') {
				// If the cell is alive
				neighbors++;
			}
		}
		// Post-condition: Bottom three cells have been counted
	}

	// Get left neighbor
	// Test if cell is on first column and alive
	if(x != 0 && grid[y][x - 1] == 'x') {
		// If cell is not on first column but is alive
		neighbors++;
	}

	// Get right neighbor
	// Test if cell is on last column and alive
	if(x != columns - 1 && grid[y][x + 1] == 'x') {
		// If cell is not on last column but is alive
		neighbors++;
	}

	return neighbors;
}

/**
 * Tests if the current grids are stuck
 * @param gridOld The previous generation
 * @param gridCurrent The current generation
 * @param gridFuture The future generation
 * @param rows The number of rows on the grids
 * @param columns The number of columns on the grids
 * @return Whether the grids are stuck (1 if stuck, 0 if not)
 */
int stuckGrids(char** gridOld, char** gridCurrent, char** gridFuture,
		int rows, int columns) {
	return equal2Dchar(gridOld, gridFuture, rows, columns) ||
			equal2Dchar(gridCurrent, gridFuture, rows, columns);
}

/**
 * Test if any cells are still alive
 * @param grid The 2D character grid to test
 * @param rows The number of rows in the grid
 * @param columns The number of columns in the grid
 * @return Whether there are still alive cells (1 if alive, 0 if none)
 */
int hasAlive(char** grid, int rows, int columns) {
	//Pre-condition: cells not yet checked
	for(int i = 0; i < rows; i++) {
		// Loop Invariant: 0 < i < rows
		// Pre-condition: row not yet checked
		for(int j = 0; j < columns; j++) {
			// Loop Invariant: 0 < j < columns
			// Test if the cell is alive
			if(grid[i][j] == 'x') {
				// If cell is alive
				return 1;
			}
		}
		// Post condition: row is checked
	}
	//Post-condition: grid is checked
	return 0;
}
