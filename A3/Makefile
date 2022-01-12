CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

TESTS = test1 test2 test3

all: list.o

list.o: list.c
	$(CC) $(CFLAGS) -c list.c -o list.o

test1: test1.o list.o 
	$(CC) $(CFLAGS) test1.o list.o -o test1

test2: test2.o list.o 
	$(CC) $(CFLAGS) test2.o list.o -o test2 -DLIST

test3: test3.o list.o 
	$(CC) $(CFLAGS) test3.o list.o -o test3

clean:
	rm *o $(TESTS)