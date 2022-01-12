#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STRLEN 128
#define TOTAL_RECORDS 100
#define CAPACITY 200


struct record
{
  char last_name[STRLEN];
  char first_name[STRLEN];
  char phone_number[13];
};

void read_file( struct record record[TOTAL_RECORDS] )
{
  FILE *fp;
  char buffer[ STRLEN ];
  int i;

  fp = fopen( "names1.txt", "r" );
  fgets( buffer, STRLEN, fp );

  for (i=0;i<TOTAL_RECORDS;i++)
  {
    // this code is not robust, buffer overflows or EOF not detected
    fscanf( fp, "%s %s", record[i].first_name, record[i].last_name );
    fscanf( fp, "%s", record[i].phone_number );
  }

  fclose( fp );
}


int char2int( unsigned char c )
  // convert a printable character to an integer in the range 0-26.
{
  if ( isupper(c) )
  {
    return (int)(c-'A');        // A=0, B=1, C=2, ...
  }
  if ( islower(c) )
  {
    return (int)(c-'a');        // a=0, b=1, c=2, ...
  }
  return 26;                    // anything else = 26
}

int str2int( char *s, int max )
  // convert a string into a number between 0 and max (not inclusive)
{
  char *c;

 
  unsigned long number, column, new;

  // convert number to base 27 number
  number = 0;
  column = 1;
  for (c=s;(*c);c++)
  {
    number += char2int(*c) * column;
    column *= 27;
  }

  // convert number to a base max number and add up the column values
  new = 0;
  while (number)
  {
    new = (new + (number % max)) % max;
    number = number/max;
  }

  return (int)new;
}

int hash_first_name( void *ptr, int max )
{
  struct record *rec;

  rec = ptr;
  return str2int( rec->first_name, max );
}

int hash_last_name( void *ptr, int max )
{
  struct record *rec;

  rec = ptr;
  return str2int( rec->last_name, max );
}

int comp_first_name( const void *ptr1, const void *ptr2 )
{
  const struct record *rec1, *rec2;
  int result;

  rec1 = ptr1;
  rec2 = ptr2;

  result = strcmp( rec1->first_name, rec2->first_name );

#ifdef DEBUG
  printf( "strcmp( \"%s\", \"%s\" )=%d\n", 
          rec1->first_name, rec2->first_name, result );
#endif
  return result;
}

int comp_last_name( const void *ptr1, const void *ptr2 )
{
  const struct record *rec1, *rec2;
  int result;

  rec1 = ptr1;
  rec2 = ptr2;

  result = strcmp( rec1->last_name, rec2->last_name );
#ifdef DEBUG
  printf( "strcmp( \"%s\", \"%s\" )=%d\n", 
          rec1->last_name, rec2->last_name, result );
#endif
  return result;
}


int main( int argc, char **argv )
{
  struct record record[TOTAL_RECORDS];	// the records
  struct record tmp, *ptr;	// tmp to hold search term, *ptr found item

  struct Performance *performance = newPerformance();
  struct HashTable *by_last_name;	// a HashTable based on last_name
  struct HashTable *by_first_name;	// a HashTable based on first_name

  int i;


  // read names and phone numbers for the file, into record
  read_file( record );
  printf( "File read\n" );

  // create 2 HashTables and store all the records in them
  by_last_name = createTable( performance, CAPACITY, 
                              &hash_last_name, comp_last_name );
  by_first_name = createTable( performance, CAPACITY, 
                              &hash_first_name, comp_first_name );
  for (i=0;i<TOTAL_RECORDS;i++)
  {
    addElement( performance, by_last_name, &(record[i]) );
    addElement( performance, by_first_name, &(record[i]) );
  }
  printf( "Hashes built\n" );
  printf( "reads:   %5d\n", performance->reads );
  printf( "writes:  %5d\n", performance->writes );
  printf( "mallocs: %5d\n", performance->mallocs );
  printf( "frees:   %5d\n", performance->frees );



  // search by last_name == Pollard
  strcpy( tmp.last_name, "Pollard" );
  ptr = getElement( performance, by_last_name, &tmp );

  if (ptr)
  {
    printf( "%s, %s.....%s\n", ptr->last_name, ptr->first_name, 
                               ptr->phone_number );
  }
  else
  {
    printf( "Not found\n" );
  }

  printf( "reads:   %5d\n", performance->reads );
  printf( "writes:  %5d\n", performance->writes );
  printf( "mallocs: %5d\n", performance->mallocs );
  printf( "frees:   %5d\n", performance->frees );

  // search by first_name == Frida
  strcpy( tmp.first_name, "Frida" );
  ptr = getElement( performance, by_first_name, &tmp );
  if ( ptr )
  {
    printf( "%s, %s.....%s\n", ptr->last_name, ptr->first_name, 
                               ptr->phone_number );
  }
  else
  {
    printf( "Not found\n" );
  }

  printf( "reads:   %5d\n", performance->reads );
  printf( "writes:  %5d\n", performance->writes );
  printf( "mallocs: %5d\n", performance->mallocs );
  printf( "frees:   %5d\n", performance->frees );

  // search by last_name == Kremer
  strcpy( tmp.last_name, "Kremer" );
  ptr = getElement( performance, by_last_name, &tmp );
  if ( ptr )
  {
    printf( "%s, %s.....%s\n", ptr->last_name, ptr->first_name, 
                               ptr->phone_number );
  }
  else
  {
    printf( "Not found\n" );
  }


  freeTable( performance, by_last_name );
  freeTable( performance, by_first_name );

  printf( "reads:   %5d\n", performance->reads );
  printf( "writes:  %5d\n", performance->writes );
  printf( "mallocs: %5d\n", performance->mallocs );
  printf( "frees:   %5d\n", performance->frees );

  free( performance );
}
