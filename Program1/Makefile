#declare the variable
CC=gcc

CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra
CFLAGS=-c -Wall -Wextra

all: hello

hello: linked_list.o list_external.o
	$(CC) linked_list.o list_external.o -o hello

linked_list.o: linked_list.c
	$(CC) $(CFLAGS) linked_list.c

list_external.o: list_external.c
	$(CC) $(CFLAGS) list_external.c

clean:
	rm -rf *o hello