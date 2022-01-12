#include "array.h"

struct Performance *newPerformance(){
    struct Performance *ptr = (struct Performance *) calloc(1,sizeof(struct Performance));
    ptr->frees=0;
    ptr->mallocs=0;
    ptr->reads=0;
    ptr->writes=0;

    return ptr;
}
struct Array *newArray( struct Performance *performance, unsigned int width, unsigned int capacity ){
    struct Array *ptr;
    if ((ptr = (struct Array *) calloc(1,sizeof(struct Array)))){
        ptr->width=width;
        ptr->capacity=capacity;
        ptr->nel=0;
        ptr->data=(void *) calloc(width*capacity,1);

        performance->mallocs++;

        return ptr;
    }else{
        fprintf(stderr, "Error - Function (newArray) \n");
        exit(0);
    }
    return 0;
}

void readItem( struct Performance *performance, struct Array *array, unsigned int index, void *dest ){
    if (index>=array->nel){
        fprintf(stderr, "Error - Function (readItem)\n");
        exit(0);
    }

    int i;
    unsigned char *ptr_src=(unsigned char *) array->data+(index*array->width);
    unsigned char *ptr_dest=(unsigned char *) dest;

    for (i=0;i<array->width;i++){
        ptr_dest[i]=*ptr_src++;
    }

    performance->reads++;
}

void writeItem( struct Performance *performance, struct Array *array, unsigned int index, void *src ){
    if (index>array->nel || index>=array->capacity){
        fprintf(stderr, "Error - Function (writeItem)\n");
        exit(0);
    }

    int i;
    unsigned char *ptr_src=(unsigned char *) src;
    unsigned char *ptr_dest=(unsigned char *) array->data+(index*array->width);

    for (i=0;i<array->width;i++){
        ptr_dest[i]=*ptr_src++;
    }
    
    if (index==array->nel) array->nel++;
    performance->writes++;
}

void contract( struct Performance *performance, struct Array *array ){
    if(array->nel==0){
        fprintf(stderr, "Error - Function (contract)\n");
        exit(0);
    }
    array->nel--;
}

void freeArray( struct Performance *performance, struct Array *array ){
    free(array->data);
    free(array);
    performance->frees++;
}

void appendItem( struct Performance *performance, struct Array *array, void *src ){
    writeItem(performance,array,array->nel,src);
}

void insertItem( struct Performance *performance, struct Array *array, unsigned int index, void *src ){
    int i;
    void *ptr=(void *) malloc(array->width);

    for (i=array->nel;i>index;i--){
        readItem(performance,array,i-1,ptr);
        writeItem(performance,array,i,ptr);
    }

    writeItem(performance,array,index,src);

    free(ptr);
}

void prependItem( struct Performance *performance, struct Array *array, void *src ){
    insertItem(performance,array,0,src);
}

void deleteItem( struct Performance *performance, struct Array *array, unsigned int index ){
    int i;
    void *ptr=(void *) malloc(array->width);

    for (i=index;i<array->nel-1;i++){
        readItem(performance,array,i+1,ptr);
        writeItem(performance,array,i,ptr);
    }

    free(ptr);
    contract(performance,array);
}
