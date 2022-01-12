#include "tree.h"

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

void attachNode( struct Performance *performance, struct Node **node_ptr, void *src, unsigned int width ){

    // Create new node
    struct Node *ptr;

    // Checking malloc
    if ((ptr = (struct Node *) malloc(sizeof(struct Node)))){
        // Malloc width bytes of data for ptr->data
        ptr->data= (void *) malloc(width);

        // Copy data from src
        memcpy(ptr->data,src,width+1);

        // Setting lower/greater pointers to NULL
        ptr->lt=NULL;
        ptr->gte=NULL;

        (*node_ptr)=ptr;

        performance->mallocs++;
        performance->writes++;
    }else{
        // Case of error
        fprintf(stderr, "Error - Function (attachNode) \n");
        exit(0);
    }
}

int comparNode( struct Performance *performance, struct Node **node_ptr,int (*compar)(const void *, const void *), void *target ){
    performance->reads++;
    return compar(target, (*node_ptr)->data);
}

struct Node **next( struct Performance *performance, struct Node **node_ptr, int direction ){

    if (isEmpty(performance,node_ptr)==1){
        // Case of error
        fprintf(stderr, "Error - Function (next) \n");
        exit(0);
    }else{

        performance->reads++;

        if (direction>=0){
            return &((*node_ptr)->gte);
        }else{
            return &((*node_ptr)->lt);
        }
    }

    return NULL;
}

void readNode( struct Performance *performance, struct Node **node_ptr, void *dest, unsigned int width ){
    if (isEmpty(performance,node_ptr)==1){
        // Case of error
        fprintf(stderr, "Error - Function (readNode) \n");
        exit(0);
    }else{

        // Copy data from src
        memcpy(dest,(*node_ptr)->data,width);

        performance->reads++;
    }
}

void detachNode( struct Performance *performance, struct Node **node_ptr ){
    if (isEmpty(performance,node_ptr)==1){
        // Case of error
        fprintf(stderr, "Error - Function (detachNode) \n");
        exit(0);
    }else{

        // Free data
        free((*node_ptr)->data);

        // Free node
        free(*node_ptr);
        *node_ptr=NULL;

        performance->frees++;
    }
}

int isEmpty( struct Performance *performance, struct Node **node_ptr ){
    return ((*node_ptr)==NULL);
}

void addItem( struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *src, unsigned int width ){
    // Check if list is empty
    if (isEmpty(performance,node_ptr)==1){
      attachNode(performance,node_ptr,src,width);
    }else{
      addItem(performance,next(performance,node_ptr,comparNode(performance,node_ptr,compar,src)), compar,src,width);
    }
}

void freeTree( struct Performance *performance, struct Node **node_ptr){
    if (isEmpty(performance,node_ptr)==0){
        freeTree(performance,next(performance,node_ptr,1));
        freeTree(performance,next(performance,node_ptr,-1));
        detachNode(performance,node_ptr);
    }
}

int searchItem( struct Performance *performance, struct Node **node_ptr,int (*compar)(const void *, const void *),void *target, unsigned int width ){

    // Check if end of tree has been reached
    if (isEmpty(performance,node_ptr)==1){
        return 0;
    }

    // Check if correct node has been found, otherwise this represents the next direction
    int direction = comparNode(performance,node_ptr,compar,target);

    // Check if match has been found and output to target
    if (direction==0){
        readNode(performance,node_ptr,target,width);
        return 1;
    }

    // Recursive function call
    return searchItem(performance,next(performance,node_ptr,direction),compar,target,width);
}