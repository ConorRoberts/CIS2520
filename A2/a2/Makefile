CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

EXECUTABLES = test_getbytes test_getbits test_bits2ull test_bits2ll test_spff test_dpff

all: array.o

array.o: array.c
	$(CC) $(CFLAGS) -c array.c -o array.o

clean:
	rm *o