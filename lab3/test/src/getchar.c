#include "putchar.h"
#include "getchar.h"

char getchar(void)
{
  char in_c;

  while (!RI);
  in_c = SBUF;
  RI = 0;

  return in_c;
}
