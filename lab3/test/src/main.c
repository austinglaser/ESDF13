#include "main.h"

int main(void)
{
  char c;

  while(1) {
    c = getchar();
    putchar(' ');
    printn(c, 16, 0);
    putchar('\n');
  }
}
