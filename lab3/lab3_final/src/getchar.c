#include "putchar.h"
#include "getchar.h"

// returns the next character in the uart buffer
char getchar(void)
{
  char in_c;

  // wait until a character is available
  while (!RI);
  
  // grab it and set up for the next xfer
  in_c = SBUF;
  RI = 0;

  // return character
  return in_c;
}
