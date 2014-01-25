#include "lab3_malloc.h"

unsigned char xdata __at(0x000C) heap[HEAP_SIZE];

void malloc_setup(void)
{
  init_dynamic_memory((MEMHEADER xdata *)heap, HEAP_SIZE);
}
