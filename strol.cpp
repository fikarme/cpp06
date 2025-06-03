#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */

int main ()
{
  char szNumbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
  char * pEnd;
  long int li1, li2, li3, li4;
  li1 = strtol (szNumbers,&pEnd,10);
  li2 = strtol (pEnd,&pEnd,16);
  li3 = strtol (pEnd,&pEnd,2);
  li4 = strtol (pEnd,NULL,0);
  printf ("The decimal equivalents are: %ld, %ld, %ld and %ld.\n", li1, li2, li3, li4);
  return 0;
}

// The decimal equivalents are: 2001, 6340800, -3624224 and 7340031

string str = "Hello";

// Internal C++ string object:
// [size][capacity][data_pointer] → ['H']['e']['l']['l']['o']['\0']

const char* cstr = str.c_str();
// Returns pointer to: ['H']['e']['l']['l']['o']['\0']
//                      ↑ cstr points here