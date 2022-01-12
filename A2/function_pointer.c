#include <stdio.h>
#include <string.h>


/* example of how to use a file pointer */

int cmp( const void *v1, const void *v2 )
/* this is a function that will be used to compare to strings */
{
  const char *s1, *s2;	/* define char pointers because our data is strings */

  s1 = v1;	/* assign the two pointers to the input data */
  s2 = v2;

  return strcmp(s1,s2);	/* use string comparison to compare the strings */
}

void use_cmp( int(*compar)(const void *, const void *), char *s1, char *s2 )
/* this is a function that accepts a function pointer to compare strings 
 * and print some information about them 
 */
{
  int compar_result;

  compar_result = compar( s1, s2 );	// call the function, store the result
  if ( compar_result<0 )
  {
    printf( "%s < %s\n", s1, s2 );
  }
  else if ( compar_result==0 )
  {
    printf( "%s == %s\n", s1, s2 );
  }
  else
  {
    printf( "%s > %s\n", s1, s2 );
  }
}

int main( int argc, char **argv )
{
  char *s1 = "hello", *s2="world";
  /* call the function use_cmp with the function poitner cmp as an argument */
  use_cmp( &cmp, s1, s2 );
  use_cmp( &cmp, s2, s1 );
  use_cmp( &cmp, s1, s1 );
}


