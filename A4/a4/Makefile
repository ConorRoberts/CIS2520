CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

FILENAME = tree

all: $(FILENAME)

$(FILENAME).o: $(FILENAME).c
	$(CC) $(CFLAGS) -c $(FILENAME).c -o $(FILENAME).o

clean:
	rm *o