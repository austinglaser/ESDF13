#include "printn.h"

void printn(int val, int base, int n_digits)
{
  char str[32];
  char digit;
  char offset;

  int i;
  for (i = 0; i < 32; i++) str[i] = '0';

  if (val < 0) putchar('-');

  for (i = 0; val; i++) {
    digit = abs(val % base);
    
    if (digit <= 9) offset = '0';
    else            offset = ('A' - 10);

    str[i] = digit + offset;
    val /= base;
  }

  if (n_digits == 0 && i == 0) putchar('0');

  if (n_digits > 0) {
    i = (n_digits < i) ? i : n_digits;
  }

  for (i--; i >= 0; i--) {
    putchar(str[i]);
  }
}
