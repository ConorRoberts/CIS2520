#include <stdio.h>
#include <stdlib.h>
#include "array.h"

/* This program will fill an array of integers of size 100 with the first 
 * 20 digits of the Fibonacci series.  It will then print out the first 
 * 20 digits, and finally report the number of read, write, malloc and free 
 * calls.
 */

#define	CAPACITY	100	// total capacity of the array
#define NEL		 20	// number of elements of the series to include

int main( int argc, char **argv )
{
  int data1=1, data2=1, tmp, i;
  struct Performance *perf;
  struct Array *array;

  perf = newPerformance();
  array = newArray( perf, sizeof( int ), CAPACITY );

  for (i=0;i<NEL;i++)
  {
    writeItem( perf, array, array->nel, &data1 );
    tmp = data2;
    data2 = data1+data2;
    data1 = tmp;
  }

  for (i=0;i<NEL;i++)
  {
    readItem( perf, array, i, &data1 );
    printf( "%d %d\n", i, data1 );
  }

  freeArray( perf, array );

  printf( "reads:   %5d\n", perf->reads );
  printf( "writes:  %5d\n", perf->writes );
  printf( "mallocs: %5d\n", perf->mallocs );
  printf( "frees:   %5d\n", perf->frees );

  free( perf );
}
