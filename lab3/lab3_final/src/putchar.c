#include "putchar.h"

void putchar(char in_c)
{
  if (in_c == '\n') {
    while (!TI);
    TI = 0;
    SBUF = 0x0D;
  }

  while (!TI);
  TI = 0;
  SBUF = in_c;
}
