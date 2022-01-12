#include "ttt.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Required function calls
    init_boards();
    init_board(START_BOARD);
    join_graph(START_BOARD);
    compute_score();

    // Loop through command line args
    for (int i = 1; i < argc; i++)
    {
        int current = atoi(argv[i]);
        print_node(htable[current]);
    }
}