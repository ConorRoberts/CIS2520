#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "hashfn.h"

typedef struct obj
{
    int hash_value;
    int hash_key;
    char value[STRLEN];
    char key[STRLEN];
} obj;

// Function to handle writing with collision
void collision_search(FILE *fp, int index_start, int to_write, int capacity)
{
    int iterations = 0;
    int i = index_start;
    int *tmp = malloc(sizeof(int));

    while (iterations < capacity)
    {

        read_index(fp, i, tmp);

        // If index is free in target file
        if (tmp)
        {
            write_index(fp, to_write, i);
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

    free(tmp);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s filename.kv capacity\n", argv[0]);
        exit(1);
    }

    char key[STRLEN];
    char value[STRLEN];
    int capacity = atoi(argv[2]);
    int i = 0;

    obj objects[capacity];

    // fix monkey file names
    char khs[STRLEN];
    strcpy(khs, argv[1]);
    khs[strlen(khs) - 2] = '\0';
    strcat(khs, "khs");
    char vhs[STRLEN];
    strcpy(vhs, argv[1]);
    vhs[strlen(vhs) - 2] = '\0';
    strcat(vhs, "vhs");

    FILE *fp = fopen(argv[1], "rb");
    FILE *key_file = fopen(khs, "wb+");
    FILE *value_file = fopen(vhs, "wb+");

    write_empty(key_file, capacity);
    write_empty(value_file, capacity);

    // Populate object list with this garbage lol
    for (i = 0; i < capacity; i++)
    {
        read_keyval(fp, key, value);

        strcpy(objects[i].key, key);
        strcpy(objects[i].value, value);
        objects[i].hash_key = hashfn(key, capacity);
        objects[i].hash_value = hashfn(value, capacity);
    }

    // Write to files correctly
    for (i = 0; i < capacity; i++)
    {
        collision_search(key_file, objects[i].hash_key, i, capacity);
        collision_search(value_file, objects[i].hash_value, i, capacity);
    }

    fclose(fp);
    fclose(key_file);
    fclose(value_file);

    return 0;
}
