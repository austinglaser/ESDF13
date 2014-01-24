#include "main.h"

extern unsigned char xdata heap[HEAP_SIZE];

void setup(void);

#define BUFF_LEN 128

int main(void)
{
  char buffer[BUFF_LEN];
  int i;
  printf("Hi, welcome!\n");

  while (1) {
  printf("Enter a string (truncates after 128 chars): ");

  getstring(buffer, BUFF_LEN);

  printf("You entered \"");
  for (i = 0; buffer[i]; i++) putchar(buffer[i]);
  putchar('"');
  putchar('\n');
  }
}

void setup(void)
{
  malloc_setup();
}
