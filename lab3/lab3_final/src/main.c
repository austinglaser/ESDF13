#include "main.h"

extern unsigned char xdata heap[HEAP_SIZE];

void setup(void);

int main(void)
{
  char c;
  char buffer[128];
  int i;
  printf("Hi, welcome!\n");

  while (1) {
  printf("Enter a string (truncates after 128 chars): ");


  for (i = 0; i < 127; i++) {
    c = getchar();
    if (c == '\n' || c == '\r') {
      putchar('\n');
      break;
    }
    buffer[i] = c;
  }
  buffer[i] = '\0';

  printf("You entered \"");

  for (i = 0; buffer[i]; i++) putchar(buffer[i]);
  putchar('\n');
  putchar('"');
  }
}

void setup(void)
{
  malloc_setup();
}
