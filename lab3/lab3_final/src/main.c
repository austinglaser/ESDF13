#include "main.h"

extern unsigned char xdata heap[HEAP_SIZE];

void setup(void);

int main(void)
{
  char c;
  char buffer[128];
  int i;
  printf("Hi, welcome!\n");

  printf("Enter a string (truncates after 128 chars): ");


  for (i = 0; i < 127; i++) {
    c = getchar();
    if (c == '\n') break;
    buffer[i] = c;
  }
  buffer[i] = '\0';


  printf("You entered %s!\n", buffer);


  while(1);
}

void setup(void)
{
  malloc_setup();
}
