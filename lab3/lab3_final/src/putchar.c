#include "putchar.h"

void putchar(int c)
{
  if (c == '\n') {
    while (!TI);
    TI = 0;
    SBUF = 0x0D;
  }

  while (!TI);
  TI = 0;
  SBUF = c;
}
