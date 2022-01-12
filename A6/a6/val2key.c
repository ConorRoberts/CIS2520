#include <stdlib.h>
#include <stdio.h>
#include "util.h"

int main(int argc, char *argv[]){
    if (argc !=2){
        fprintf( stderr, "Usage: %s filename.kv ‘search term’\n", argv[0] );
        exit(1);
    }

    FILE *fp = fopen(argv[1],"rb");

    return 0;
}