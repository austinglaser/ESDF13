#include "putchar.h"

char getchar(void c)
{
  char in_c;

  while (!RI);
  in_c = SBUF;
  RI = 0;

  return in_c;
}
