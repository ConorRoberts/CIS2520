#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

/* This program will fill an array of strings of size 100 with 
 * a bunch of names from the file "names3.txt".
 * It will then search for a bunch of names using searchItem.
 * Each time it will report the number of read, write, malloc and free 
 * calls.  Finally it searches for every name in the table and computes
 * the average number of reads per search.
 */

#define	CAPACITY	100	// total capacity of the array
#define STRLEN		50


void readFile( struct Performance *performance, struct Array *array )
{
  FILE *fp;
  char name[STRLEN];
  char *retval;

  fp = fopen( "names3.txt", "r" );

  while (!feof(fp))
  {
    retval = fgets( name, STRLEN, fp );

    if (retval!=NULL)
    {
      name[strlen(name)-1]='\0'; // replace \n with \0
      writeItem( performance, array, array->nel, &name );
    }
  }

  fclose( fp );
}

int cmp( const void *v1, const void *v2 )
{
  const char *s1, *s2;

  s1 = v1;
  s2 = v2;

  // printf( "cmp(\"%s\",\"%s\")\n", s1, s2 );
  return strcmp(s1,s2);
}

int main( int argc, char **argv )
{
  struct Performance *perf, *search_perf;
  struct Array *array;
  int i;
  int test;
  char *test_names[6] = { "Aguilar, Herbert",
                         "Dominguez, Keon",
                         "Juarez, Brielle",
			 "Reid, Lilly-May",
			 "Yu, Mahdi",
			 "Kremer, Stefan" };
  char name[STRLEN];

  // load the data into the array
  perf = newPerformance();
  array = newArray( perf, STRLEN, CAPACITY );
  readFile( perf, array );
  printf( "Read %d records\n", array->nel );
  free( perf );

  // run 6 tests and print the results
  for (test=0;test<6;test++)
  {
    perf = newPerformance();
    i=searchItem( perf, array, &cmp, test_names[test] );
    printf( "%s: i=%d\n", test_names[test], i );

    printf( "reads:   %5d\n", perf->reads );
    printf( "writes:  %5d\n", perf->writes );
    printf( "mallocs: %5d\n", perf->mallocs );
    printf( "frees:   %5d\n", perf->frees );

    free( perf );
    printf( "\n" );
  }

  // run two separate counters (one just for search operations)
  search_perf = newPerformance();
  perf = newPerformance();

  for (test=0;test<CAPACITY;test++)
  {
    readItem( perf, array, test, name );
    i = searchItem( search_perf, array, &cmp, name );
  }

  printf( "Average reads per search:  %6.3f\n", (search_perf->reads)/(double)CAPACITY );

  freeArray( perf, array );
  free( perf );
  free( search_perf );
}

