# Jonathan Chang
# CS 2303 C01 18
# Assignment 2 - Game of Life
# life.c
#

# Set CFLAGS to activate all warnings and enable debugger
CFLAGS = -Wall -g

# Default rule is to build the executable called life
all: life

# Rule for building the executable.
life: life.o twoD.o
	gcc $(CFLAGS) life.o twoD.o -o life -lm

# Rules for building each object file.
life.o: life.c twoD.h
	gcc $(CFLAGS) -c life.c -lm

twoD.o: twoD.c twoD.h
	gcc $(CFLAGS) -c twoD.c -lm

# Give command "make clean" to remove object files,
#  executable, and documentation.
clean:
	rm -f *.o life
	rm -f -r html latex

# Give command "make docs" to create documentation.	
docs:
	doxygen
