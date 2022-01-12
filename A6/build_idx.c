#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "hashfn.h"

// Function to handle writing with collision
void collision_search(FILE *fp, FILE *to_write, int hash, int index, int capacity)
{
    read_index(fp,hash,&index);
        while(index!=-1){
            hash++;
            if(hash==capacity){
                hash=0;
            }
            read_index(fp,hash,&index);
        }
        write_index(fp,to_write,index);
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
    int index;

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
        int hash_key = hashfn(value,capacity);
        int hash_val = hashfn(value,capacity);

        read_index(key_file,hash_key,&index);
        while(index!=-1){
            hash_key++;
            if(hash_key==capacity){
                hash_key=0;
            }
            read_index(key_file,hash_key,&index);
        }
        write_index(key_file,hash_key,index);

    }

    // Write to files correctly
    // for (i = 0; i < capacity; i++)
    // {
    //     collision_search(key_file, objects[i].hash_key, i, capacity);
    //     collision_search(value_file, objects[i].hash_value, i, capacity);
    // }

    fclose(fp);
    fclose(key_file);
    fclose(value_file);

    return 0;
}
