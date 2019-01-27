Jonathan Chang
CS 2303 C01 18
Assignment 2 - Game of Life
README

This program simulates a Game of Life based on the input of a text file. As such, from generation to generation it follows all of the standard rules: an alive cell with 1 or less neighbors or 4 or more neighbors dies, and an empty space surrounded by exactly 3 alive cells will spawn an alive cell. This process will continue until the specified number of generations is reach, all cells die, or the grid reachs a point were the pattern repeats or is stuck. 

This program can be complied using the make command:
make life

This program can then be run using the following command:
./life %d %d %d %s %c %c

Required Arguements:
(%d) The desired width of the grid
(%d) The desired height of the grid
(%d) The desired number of generations
(%s) The text file to read from

Optional Arguemnts:
(%c) Whether to print out each generation (y/n)
(%c) Whether to pause between generations (y/n) (Press ENTER betwwen generations)
Default values are 'n' for all optional arguments

For example, the command
./life 9 10 100 example.txt y n
Would create a grid with 9 width and 10 height and run 100 generations using the given pattern in example.txt. It would print out each generation but the user would not have to hit enter between generations.

Complications:
Fortunately, there were relatively minimum complications in the writing of this assignment - by working in a top-down fashion, there were a number o futility functions that were written well before they were ever used. Furthermore, by breaking the problem down into chunks no function outside of main, ever became too big. The main two problems that were encountered were that for the pointers changed inside of functions do not affect the pointer outside of the function and that midway through life.c was wiped. To fix the first problem, one function was moved directly into main so that the pointers would all remain constant. For the second, this loss of data resulted from the inablility of the virtual machine to regain empty space (this virtual machine was used for several classes before this one); this resulted in life.c being unable to save and when "Save as" was used, it saved a blank file. Luckily all other files were saved and another new virtual machine was created.

No external sources were used.

Loop Invariants:
life.c.109: This while loop will terminate if one of the conditions is not met namely it has no yet reached the desired generation number, there are still cells alive on the grid, and that the pattern of alive cells is changing.
life.c:169: This loop is used to parse through each row on a grid, therefore i must remain between 0 and the number of rows.
life.c:172: This loop is used to parse through each character on a row, therefore j must remain between 0 and the number of columns.
life.c:229: This loop is used to check the top cells of a particular cell, given that the cell might be on any end of a row, the start and end of the loop are varaible depending on the location of the cell.
life.c:255: This loop is used to check the bottom cells of a particular cell, given that the cell might be on any end of a row, the start and end of the loop are varaible depending on the location of the cell.
life.c:307: This loop is used to parse through each row on a grid, therefore i must remain between 0 and the number of rows.
life.c:310: This loop is used to parse through each character on a row, therefore j must remain between 0 and the number of columns.

twoD.c:29: This loop is used to parse through each row in a grid, therefore i must remained betweee n0 and the number of rows.
twoD.c:52: This loop is used to parse through each row on a grid, therefore i must remain between 0 and the number of rows.
twoD.c:55: This loop is used to parse through each character on a row, therefore j must remain between 0 and the number of columns.
twoD.c:74: This loop is used to parse through each row on a grid, therefore i must remain between 0 and the number of rows.
twoD.c:77: This loop is used to parse through each character on a row, therefore j must remain between 0 and the number of columns.
twoD.c:96: This loop is used to parse through each row on a grid, therefore i must remain between 0 and the number of rows.
twoD.c:99: This loop is used to parse through each character on a row, therefore j must remain between 0 and the number of columns.
twoD.c:126: This loop is used to parse through each row on a grid, therefore i must remain between 0 and the number of rows.
twoD.c:129: This loop is used to parse through each character on a row, therefore j must remain between 0 and the number of columns.
twoD.c:160: This while loop goes through the file line by line and terminates only if it runs out of lines to read or it reaching the desired number of rows.
twoD.c:162 This loop goes through the line and terminates if it reaches the end of the line or by reaching the desired number of columns
twoD.c:186 This loop only goes thorugh the number of input rows, therefore i must remained between 0 and the number of input rows.
twoD.c:189 This loop only goes htorugh the nubmer of inout oclumns, therefore j must remained between 0 and the number of input columns.
twoD.c:210 This loop is used to parse through each row in a grid, therefore i must remained betweee n0 and the number of rows.
