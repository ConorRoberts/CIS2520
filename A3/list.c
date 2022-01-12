#include "list.h"

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
    return 0;
}
void push( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ){
    struct Node *node_ptr;

    // Checking malloc
    if ((node_ptr = (struct Node *) malloc(sizeof(struct Node)))){

        // Set next link to old structure
        node_ptr->next = *list_ptr;

        // Malloc for new data
        node_ptr->data = (void *) malloc(width);

        // Copy data into new structure
        memcpy(node_ptr->data,src,width);

        // Replace list_ptr with new node

        (*list_ptr)=node_ptr;

        performance->writes++;
        performance->mallocs++;

    }else{
        // Case of error
        fprintf(stderr, "Error - Function (push) \n");
        exit(0);
    }
}
void readHead( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width ){
    if (!isEmpty(performance,list_ptr)){
        memcpy(dest,(*list_ptr)->data,width);
        performance->reads++;
    }else{
        // Case of error
        fprintf(stderr, "Error - Function (readHead) \n");
        exit(0);
    }
}
void pop( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width ){
    if (!isEmpty(performance,list_ptr)){

        // Copy data to destination
        memcpy(dest,(*list_ptr)->data,width);

        // Moving list_ptr ahead
        struct Node *head = (*list_ptr);
        (*list_ptr)=(*list_ptr)->next;

        performance->frees++;
        performance->reads++;

        // Freeing old list_ptr head
        free(head->data);
        free(head);
    }else{
        // Case of error
        fprintf(stderr, "Error - Function (pop) \n");
        exit(0);
    }
}

struct Node **next( struct Performance *performance, struct Node **list_ptr){
    if (!isEmpty(performance,list_ptr)){
        performance->reads++;
        return (&(*list_ptr)->next);
    }else{
        // Case of error
        fprintf(stderr, "Error - Function (next) \n");
        exit(0);
    }

    return NULL;
}
int isEmpty( struct Performance *performance, struct Node **list_ptr ){
    return (!(*list_ptr) ? 1 : 0);
}

void freeList( struct Performance *performance, struct Node **list_ptr ){
    // Temporary destination so pop succeeds
    void *dest=malloc(sizeof((*list_ptr)->data));//malloc(sizeof(struct Node));

    // Clears head of list while list is not empty
    while (!isEmpty(performance,list_ptr)){
        pop(performance,list_ptr,dest,sizeof(*list_ptr));
    }

    // Free temporary dest
    free(dest);
}

void readItem( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width ){
    int i;

    struct Node **list_cpy = list_ptr;

    // Traverse list until index is reached
    for(i=0;i<index;i++){
        list_cpy=next(performance,list_cpy);
    }

    readHead(performance,list_cpy,dest,width);
}

void appendItem( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ){
    struct Node **list_cpy = list_ptr;

    // Traverse list until end is reached
    while(!isEmpty(performance,list_cpy)){
        list_cpy=next(performance,list_cpy);
    }

    // Add node at end
    push(performance,list_cpy,src,width);
}
void insertItem( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *src, unsigned int width ){
    int i;
    struct Node **list_cpy = list_ptr;

    // Increment list_cpy until index is achieved
    for(i=0;i<index;i++){
        list_cpy=next(performance,list_cpy);
    }

    // Push new item at index
    push(performance,list_cpy,src,width);

}
void prependItem( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ){
    insertItem(performance,list_ptr,0,src,width);
}
void deleteItem( struct Performance *performance, struct Node **list_ptr, unsigned int index ){
    int i;
    struct Node **list_cpy = list_ptr;

    // Increment list_cpy until index is achieved
    for(i=0;i<index;i++){
        list_cpy=next(performance,list_cpy);
    }

    // Temporary destination so pop succeeds
    void *dest=calloc(1,sizeof((*list_ptr)->data));

    // Remove node at index and save to temp destination
    pop(performance,list_cpy,dest,sizeof(struct Node));

    free(dest);
}

int findItem( struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width ){

    int i=0;
    int index=-1;
    struct Node **list_cpy = list_ptr;
    void *dest= (void *) malloc(width);

    while(!isEmpty(performance,list_cpy)){
        readHead(performance,list_cpy,dest,width);
        if (compar(target,dest)==0){
            index=i;
            break;
        }
        list_cpy=next(performance,list_cpy);
        i++;
    }

    free(dest);

    return index;
}