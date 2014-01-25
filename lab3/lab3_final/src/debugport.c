#include "debugport.h"

void dataout(void xdata * address, char val) 
{
  __asm
    mov   dpl, r7
    mov   dph, r6
    mov   a, r5
    movx  @dptr, a
  __endasm;
}
