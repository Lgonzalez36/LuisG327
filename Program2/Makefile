#declare the variable
CC=gcc

CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra
CFLAGS=-c -Wall -Wextra

all: prog2

prog2: program2.o
	$(CC) program2.o -o prog2
	
program2.o: program2.c
	$(CC) $(CFLAGS) program2.c

clean:
	rm -rf *o prog2