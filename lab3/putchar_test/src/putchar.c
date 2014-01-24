#include "putchar.h"

int n_online = 0;

void putchar(char in_c)
{
  if (in_c == '\n') {
    while (!TI);
    TI = 0;
    SBUF = 0x0D;
    //n_online = 0;
  }

  while (!TI);
  TI = 0;
  SBUF = in_c;

  //n_online++;
}

void finish_line(char term, int len)
{
  int i;
  int padding = len - n_online;
  for (i = 0; i < padding; i++) putchar(' ');
  putchar(term);
}
