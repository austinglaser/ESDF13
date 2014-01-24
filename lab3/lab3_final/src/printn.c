#include "printn.h"

void printn(int val, int base)
{
  char str[32];
  char digit;
  char offset;

  int i;

  if (val < 0) putchar('-');

  for (i = 0; val; i++) {
    digit = abs(val % base);
    
    if (digit <= 9) offset = '0';
    else            offset = ('A' - 10);

    str[i] = digit + offset;
    val /= base;
  }

  for (i--; i >= 0; i--) {
    putchar(str[i]);
  }
}
