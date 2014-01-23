#include <at89c51ed2.h>

int putchar(int c);

int main(void)
{
  while(1) {
    putchar('U');
  }
}

int putchar(int c)
{
  if (c == '\n') {
    while (!TI);
    TI = 0;
    SBUF = 0x0D;
  }

  while (!TI);
  TI = 0;
  SBUF = c;

  return c;
}
