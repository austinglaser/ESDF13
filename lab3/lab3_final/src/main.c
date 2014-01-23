#include <at89c51ed2.h>
#include <stdio.h>

void putchar(int c);

int main(void)
{
  printf("Hi, welcome!\n");
  while(1) {
  }
}

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
