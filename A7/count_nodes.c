#include "ttt.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    // Required function calls
    init_boards();
    init_board(START_BOARD);
    join_graph(START_BOARD);

    int i;
    int count=0;
    for (i=0;i<HSIZE;i++){
        if (htable[i].init==1) 
            count++;
    }

    printf("%d\n",count);

}