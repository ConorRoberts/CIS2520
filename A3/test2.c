#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// #ifdef ARRAY
// #include "array.h"
// #elif defined LIST
// #include "list.h"
// #else
// #error You must compile this code with either the -DLIST or the -DARRAY option.
// #include <stop>
// #endif

/* This program will conduct a bunch of tests on either an array or a list.
 */

#define	CAPACITY	100	// total capacity of the array
#define NEL		 20	// number of elements of the series to include

void report( char *message, struct Performance *perf )
{
  printf( "%s", message );
  printf( "  reads:   %5d\n", perf->reads );
  printf( "  writes:  %5d\n", perf->writes );
  printf( "  mallocs: %5d\n", perf->mallocs );
  printf( "  frees:   %5d\n", perf->frees );

  perf->reads   = 0;
  perf->writes  = 0;
  perf->mallocs = 0;
  perf->frees   = 0;
}


int main( int argc, char **argv )
{
  int i;
  double number;
  struct Performance *perf;


  struct Node *list;

  perf = newPerformance();

  list = NULL;

  report( "after new\n", perf );
  printf( "\n\n" );

  // fill data structure with doubles, numbered from 0 to NEL-1
  for (i=0;i<NEL;i++)
  {
    number = i;

    appendItem( perf, &list, &number, sizeof(number) );

  }

  report( "after appendItem x 20\n", perf );
  printf( "\n\n" );

  printf( "Initial data:\n" );
  for (i=0;i<NEL;i++)
  {

    readItem( perf, &list, i, &number, sizeof(number) );

    printf( "%d %f\n", i, number );
  }

  report( "after readItem x 20\n", perf );
  printf( "\n\n" );

  // now insert the value 7.5 at index 8
  number = 7.5;

  insertItem( perf, &list, 8, &number, sizeof(number) );

  report( "after insertItem =7.5 at index 8\n", perf );
  printf( "\n\n" );

  printf( "After insert:\n" );
  for (i=0;i<NEL+1;i++)
  {

    readItem( perf, &list, i, &number, sizeof(number) );

    printf( "%d %f\n", i, number );
  }

  report( "after readItem x 21\n", perf );
  printf( "\n\n" );

  // now prepend the value -1.0
  number = -1.0;
 
   prependItem( perf, &list, &number, sizeof(number) );


  report( "after prependItem\n", perf );
  printf( "\n\n" );


  printf( "After prepend:\n" ); 
  for (i=0;i<NEL+2;i++)
  {


    readItem( perf, &list, i, &number, sizeof(number) );

    printf( "%d %f\n", i, number );
  }

  report( "after readItem x 22\n", perf );
  printf( "\n\n" );

  // delete element 16

  deleteItem( perf, &list, 16 );

  report( "after deleteItem\n", perf );
  printf( "\n\n" );

  printf( "After delete:\n" );
  for (i=0;i<NEL+1;i++)
  {

    readItem( perf, &list, i, &number, sizeof(number) );

    printf( "%d %f\n", i, number );
  }

  report( "after readItem x 21\n", perf );
  printf( "\n\n" );

  // free the data structure

  freeList( perf, &list );

  report( "after free\n", perf );
  printf( "\n\n" );


  free( perf );
}

