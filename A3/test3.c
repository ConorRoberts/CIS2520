#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* This program will fill a list of strings of size 100 with 
 * a bunch of names from the file "names3.txt".
 * It will then search for a bunch of names using findItem.
 * Each time it will report the number of read, write, malloc and free 
 * calls.  Finally it searches for every name in the table and computes
 * the average number of reads per search.
 */

#define STRLEN		50
#define CAPACITY	100


void readFile( struct Performance *performance, struct Node **list_ptr )
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
      appendItem( performance, list_ptr, name, STRLEN );
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
  struct Performance *perf, *find_perf;
  struct Node *list;
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
  list = NULL;
  readFile( perf, &list );
  free( perf );

  // run 6 tests and print the results
  for (test=0;test<6;test++)
  {
    perf = newPerformance();
    i=findItem( perf, &list, &cmp, test_names[test], STRLEN );
    printf( "%s: i=%d\n", test_names[test], i );

    printf( "reads:   %5d\n", perf->reads );
    printf( "writes:  %5d\n", perf->writes );
    printf( "mallocs: %5d\n", perf->mallocs );
    printf( "frees:   %5d\n", perf->frees );

    free( perf );
    printf( "\n" );
  }

  // run two separate counters (one just for find operations)
  find_perf = newPerformance();
  perf = newPerformance();

  for (test=0;test<CAPACITY;test++)
  {
    readItem( perf, &list, test, name, STRLEN );
    i = findItem( find_perf, &list, &cmp, name, STRLEN );
  }

  printf( "Average reads per find:  %6.3f\n", (find_perf->reads)/(double)CAPACITY );

  freeList( perf, &list );
  free( perf );
  free( find_perf );
}

