#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct HashTable{
 unsigned int capacity;
 unsigned int nel;
 void **data;
 int (*hash)( void *, int );
 int (*compar)(const void *, const void *);
};

struct Performance
{
 unsigned int reads;
 unsigned int writes;
 unsigned int mallocs;
 unsigned int frees;
};

// BASE
struct Performance *newPerformance();
struct HashTable *createTable( struct Performance *performance,unsigned int capacity,int (*hash)( void *, int ), int (*compar)(const void *, const void *) );
void addElement( struct Performance *performance, struct HashTable *table,void *src );
int getIdx( struct Performance *performance, struct HashTable *table,void *src );
void freeTable( struct Performance *performance, struct HashTable *table );

// DERIVED FUNCTIONS
void *getElement( struct Performance *performance, struct HashTable *table,void *src );
void removeElement( struct Performance *performance, struct HashTable *table,void *target );

// LAST 20%
int hashAccuracy( struct HashTable *table );
void rehash( struct HashTable *table );

#endif