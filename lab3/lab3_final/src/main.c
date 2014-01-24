#include "main.h"

extern unsigned char xdata heap[HEAP_SIZE];

void setup(void);

int main(void)
{
  printf("Hi, welcome!\n");
  printf("Type a 'c': ");
  while(getchar() != 'c');

  printf("\nYou hit the right key!");

  while(1);
}

void setup(void)
{
  malloc_setup();
}
