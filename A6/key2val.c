#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "hashfn.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s filename.kv ‘search term’\n", argv[0]);
        exit(1);
    }

    // fix monkey filename
    char khs[STRLEN];
    strcpy(khs, argv[1]);
    khs[strlen(khs) - 2] = '\0';
    strcat(khs, "khs");

    // ooh ooh ahh ahh open file 
    FILE *fp = fopen(argv[1], "rb");
    FILE *key_file = fopen(khs, "rb");

    char val[STRLEN];

    int start = hashfn(argv[2], STRLEN);

    int capacity = get_capacity(fp);

    int i = start;
    int iterations = 0;
    int found = 0;
    int *tmp = malloc(sizeof(int));
    while (iterations < capacity)
    {
        read_index(key_file, i, tmp);
        read_key(fp, *tmp, val);

        if (start == hashfn(val, STRLEN))
        {
            read_val(fp, i, val);
            printf("%s\n", val);
            found = 1;
            break;
        }
        i++;
        if (i == capacity)
        {
            i = 0;
        }

        // Increment total count
        iterations++;
    }

    if (found == 0)
    {
        printf("NOT FOUND\n");
    }

    free(tmp);

    fclose(fp);
    fclose(key_file);

    return 0;
}