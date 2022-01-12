CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

HELPERS = util.o hashfn.o

EXECUTABLES = build_idx key2val val2key actors bacon1

all: $(EXECUTABLES)

util.o: util.c
	$(CC) $(CFLAGS) -c util.c -o util.o

hashfn.o: hashfn.c
	$(CC) $(CFLAGS) -c hashfn.c -o hashfn.o

build_idx: $(HELPERS) build_idx.o 
	$(CC) $(CFLAGS) build_idx.o $(HELPERS) -o build_idx

key2val: $(HELPERS) key2val.o 
	$(CC) $(CFLAGS) key2val.o $(HELPERS) -o key2val

val2key: $(HELPERS) val2key.o 
	$(CC) $(CFLAGS) val2key.o $(HELPERS) -o val2key

actors: $(HELPERS) actors.o 
	$(CC) $(CFLAGS) actors.o $(HELPERS) -o actors

bacon1: $(HELPERS) bacon1.o 
	$(CC) $(CFLAGS) bacon1.o $(HELPERS) -o bacon1

clean:
	rm *o $(EXECUTABLES)