CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

TESTS = test1 test2 test3

FILENAME  = tree

all: $(FILENAME)

$(FILENAME).o: $(FILENAME).c
	$(CC) $(CFLAGS) -c $(FILENAME).c -o $(FILENAME).o

ttest: ttest.o $(FILENAME).o 
	$(CC) $(CFLAGS) ttest.o $(FILENAME).o -o ttest

clean:
	rm *o $(TESTS)