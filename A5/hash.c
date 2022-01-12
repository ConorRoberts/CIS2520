#include "hash.h"

struct Performance *newPerformance(){
    struct Performance *ptr;

    // Checking malloc
    if ((ptr = (struct Performance *) malloc(sizeof(struct Performance) +1))){
        ptr->frees=0;
        ptr->mallocs=0;
        ptr->reads=0;
        ptr->writes=0;

        return ptr;
    }else{
        // Case of error
        fprintf(stderr, "Error - Function (newPerformance) \n");
        exit(0);
    }

    // Catchall
    return NULL;
}

struct HashTable *createTable( struct Performance *performance,unsigned int capacity,int (*hash)( void *, int ), int (*compar)(const void *, const void *) ){
    struct HashTable *ptr;

    // Checking malloc
    if ((ptr = (struct HashTable *) malloc(sizeof(struct HashTable)))){
        if ((ptr->data=(void **) malloc(capacity * sizeof(void *)))){
            ptr->capacity=capacity;
            ptr->nel=0;
            ptr->hash=hash;
            ptr->compar=compar;

            int i;
            // Set value of each pointer in data array to null
            for (i=0;i<capacity;i++){
                ptr->data[i]=NULL;
            }

            // Increment performance->reads each time
            performance->reads+=ptr->capacity;
            performance->mallocs++;

            return ptr;
        }
    }

    // Case of error
    fprintf(stderr, "Error - Function (createTable) \n");
    exit(0);

    // Catchall
    return NULL;
}

void addElement( struct Performance *performance, struct HashTable *table,void *src ){
    if (table->nel==table->capacity){
        // Case of error
        fprintf(stderr, "Error - Function (addElement) \n");
        exit(0);
    }

    // Calculate new index with hash function
    int i = table->hash(src,table->capacity);
    int start = i;

    // Iterate through array until NULL has been found
    do{
        // Check for NULL value
        if (table->data[i]==NULL){
            table->data[i]=src;
            break;
        }

        performance->reads++;
        i++;

        // If search goes past capacity, go to zero and go again
        if (i==table->capacity){
            i=0;
        }

    }while(i!=start);

    table->nel++;
    performance->writes++;
}

int getIdx( struct Performance *performance, struct HashTable *table,void *src ){

    // Calculate new index with hash function
    int i = table->hash(src,table->capacity);
    int start = i;

    // Iterate through array until comparison has been met
    do{
        // Check for non-null so compar doesn't fail
        if(table->data[i]!=NULL){
            performance->reads++;
            if (table->compar(src,table->data[i])==0){
                return i;
            }
        }

        i++;

        // If search goes past capacity, go to zero and go again
        if (i==table->capacity){
            i=0;
        }

    }while(i!=start);

    return -1;
}

void freeTable( struct Performance *performance, struct HashTable *table ){
    performance->frees++;
    free(table->data);
    free(table);
}

void *getElement( struct Performance *performance, struct HashTable *table,void *src ){
    int index = getIdx(performance,table,src);
    return index == -1 ? NULL : table->data[index];
}
void removeElement( struct Performance *performance, struct HashTable *table,void *target ){
    table->data[getIdx(performance,table,target)]=NULL;
    performance->writes++;
    table->nel--;
}

int hashAccuracy( struct HashTable *table ){
    int i;
    int acc=0;

    for (i=0;i<table->capacity;i++){
        if (table->data[i]==NULL){
            continue;
        }

        int value = table->hash(table->data[i],table->capacity);

        if (i<value){
            acc+=i+(table->capacity-value);
        }else if(i>value){
            acc+=i-value;
        }
    }

    return acc;
}

void rehash( struct HashTable *table ){
    // Hash accuracy represnts how close hashValue is to index
    // Difference between hashValue and index
    // Create an array where all of the hashValues are optimised to be as close as possible to their index

    // Iterate through until no value changes can be made
    // A good change = Can swap into hashValue
    int i;
    for (i=0;i<table->capacity;i++){

    }
}
