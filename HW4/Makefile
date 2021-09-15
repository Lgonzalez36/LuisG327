# Makefile
#--------------------------------------------------------------
# Homework #4
#--------------------------------------------------------------
CC=gcc
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra
CFLAGS=-Wall -Wextra

ALL := hw4_malloc_test

all: ${ALL}

hw4_malloc_test: hw4_malloc.o hw4_malloc_test.c
	${CC} ${CFLAGS} -o hw4_malloc_test hw4_malloc_test.c hw4_malloc.o

hw4_malloc.o: hw4_malloc.c hw4_malloc.h
	${CC} ${CFLAGS} -c hw4_malloc.c -o hw4_malloc.o

clean:
	rm -vf ${ALL} core* *.o *~
	rm -fr *dSYM
