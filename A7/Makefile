CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

OBJ = ttt2
OBJ2 = ttt1

EXECUTABLES = show_node count_nodes

all: $(EXECUTABLES)

$(OBJ).o: $(OBJ).c 
	$(CC) $(CFLAGS) -c $(OBJ).c  -o $(OBJ).o

$(OBJ2).o: $(OBJ2).c
	$(CC) $(CFLAGS) -c $(OBJ2).c -o $(OBJ2).o

show_node: $(OBJ).o $(OBJ2).o show_node.o 
	$(CC) $(CFLAGS) show_node.o $(OBJ).o $(OBJ2).o -o show_node

count_nodes: $(OBJ).o $(OBJ2).o count_nodes.o 
	$(CC) $(CFLAGS) count_nodes.o $(OBJ).o $(OBJ2).o -o count_nodes

alphatoe: $(OBJ).o $(OBJ2).o alphatoe.o 
	$(CC) $(CFLAGS) alphatoe.o $(OBJ).o $(OBJ2).o -o alphatoe

clean:
	rm *o $(EXECUTABLES)