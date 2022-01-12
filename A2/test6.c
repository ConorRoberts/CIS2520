#include <stdio.h>
#include <stdlib.h>
#include "array.h"

/* This program will fill an array of doubles of size 100 with the first 
 * 20 non-negative integers.
 */

#define	CAPACITY	100	// total capacity of the array
#define NEL		 20	// number of elements of the series to include

int main( int argc, char **argv )
{
  int i;
  double number;
  struct Performance *perf;
  struct Array *array;

  perf = newPerformance();
  array = newArray( perf, sizeof( double ), CAPACITY );

  for (i=0;i<NEL;i++)
  {
    number = i;
    appendItem( perf, array, &number );
  }

  printf( "Initial array:\n" );
  for (i=0;i<array->nel;i++)
  {
    readItem( perf, array, i, &number );
    printf( "%d %f\n", i, number );
  }


  number = 7.5;
  insertItem( perf, array, 8, &number );

  printf( "After insert:\n" );
  for (i=0;i<array->nel;i++)
  {
    readItem( perf, array, i, &number );
    printf( "%d %f\n", i, number );
  }

  number = -1.0;
  prependItem( perf, array, &number );
 
  printf( "After prepend:\n" ); 
  for (i=0;i<array->nel;i++)
  {
    readItem( perf, array, i, &number );
    printf( "%d %f\n", i, number );
  }

  deleteItem( perf, array, 16 );

  printf( "After delete:\n" );
  for (i=0;i<array->nel;i++)
  {
    readItem( perf, array, i, &number );
    printf( "%d %f\n", i, number );
  }

  
  freeArray( perf, array );

  printf( "reads:   %5d\n", perf->reads );
  printf( "writes:  %5d\n", perf->writes );
  printf( "mallocs: %5d\n", perf->mallocs );
  printf( "frees:   %5d\n", perf->frees );

  free( perf );
}

