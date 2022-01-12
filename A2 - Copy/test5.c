#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

/* This program will fill an array of structures of size 100 with 
 * a bunch of names from the file names.txt.  It then tries to exceed
 * the capacity of the array.
 */

#define	CAPACITY	100	// total capacity of the array

struct Name
{
  char first[25];
  char last[25];
};

void readFile( struct Performance *performance, struct Array *array )
{
  FILE *fp;
  char buffer[81];
  struct Name name;
  int retval;

  fp = fopen( "names.txt", "r" );

  // skip the first line
  fgets( buffer, 80, fp );

  while (!feof(fp))
  {
    // this scanf call is unsafe if inputs are wider the first or last strings
    retval = fscanf( fp, "%s %s", name.first, name.last );

    if (retval==2)
    {
      writeItem( performance, array, array->nel, &name );
    }
  }

  fclose( fp );

  strcpy( name.first, "Stefan" );
  strcpy( name.last, "Kremer" );

  writeItem ( performance, array, array->nel, &name );
}

int main( int argc, char **argv )
{
  struct Name name;
  struct Performance *perf;
  struct Array *array;
  int i;

  perf = newPerformance();
  array = newArray( perf, sizeof( struct Name ), CAPACITY );

  readFile( perf, array );

  printf( "Read %d records\n", array->nel );

  for (i=0;i<array->nel;i++)
  {
    readItem( perf, array, i, &name );
    printf( "%2d:  %s, %s\n", i, name.last, name.first );
  }

  freeArray( perf, array );

  printf( "reads:   %5d\n", perf->reads );
  printf( "writes:  %5d\n", perf->writes );
  printf( "mallocs: %5d\n", perf->mallocs );
  printf( "frees:   %5d\n", perf->frees );

  free( perf );
}

