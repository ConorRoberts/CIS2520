CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

FILENAME = hash

all: $(FILENAME)

$(FILENAME).o: $(FILENAME).c
	$(CC) $(CFLAGS) -c $(FILENAME).c -o $(FILENAME).o

htest1: htest1.o $(FILENAME).o 
	$(CC) $(CFLAGS) -DDEBUG htest1.o $(FILENAME).o -o htest1

htest2: htest2.o $(FILENAME).o 
	$(CC) $(CFLAGS) htest2.o $(FILENAME).o -o htest2

htest3: htest3.o $(FILENAME).o 
	$(CC) $(CFLAGS) htest3.o $(FILENAME).o -o htest3

htest4: htest4.o $(FILENAME).o 
	$(CC) $(CFLAGS) htest4.o $(FILENAME).o -o htest4

clean:
	rm *o