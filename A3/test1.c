#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main( int argc, char **argv )
{
  int i,j;

  struct Performance *performance;
  struct Node *list;
  struct Node **list_ptr;

  list = NULL;
  performance = newPerformance();

  printf( "isEmpty = %d\n", isEmpty( performance, &list ) );
  // should print 1
 
  // should print isEmpty=0 and j increasing from 0 to 9 
  for (i=0;i<10;i++)
  {
    printf( "%d: ", i );
    push( performance, &list, &i, sizeof( int ) );
    readHead( performance, &list, &j, sizeof(int) );
    printf( "isEmpty = %d, ", isEmpty( performance, &list ) );
      // should print 0
    printf( "j = %d\n", j );
  }

  // should print j decreasing from 9 to 0 and isEmpty = 0
  for ( list_ptr=&list;
        (!isEmpty(performance,list_ptr));
	list_ptr=next(performance,list_ptr) )
  {
    readHead( performance, list_ptr, &j, sizeof(int) );
    printf( "%d, ", j );
  }
  printf( "isEmpty = %d\n", isEmpty( performance, &list ) );

  // should print j decreasing from 9 to 0 and isEmpty = 1
  while (!isEmpty(performance,&list))
  {
    pop( performance, &list, &j, sizeof(int) );
    printf( "%d, ", j );
  }
  printf( "isEmpty = %d\n", isEmpty( performance, &list ) );

  printf( "reads:   %5d\n", performance->reads );
  printf( "writes:  %5d\n", performance->writes );
  printf( "mallocs: %5d\n", performance->mallocs );
  printf( "frees:   %5d\n", performance->frees );

  free( performance );

  return 0;
}

