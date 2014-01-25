#include "debugport.h"

// simply writes a value to the specified address.
void dataout(char xdata * address, char val) 
{
  __asm
    ;'address' initially stored in dptr
    ;'val' stored at #_dataout_PARM_2 in xdata
    
    ;*address = val;

    ; save address value
    mov   r2, dpl
    mov   r3, dph

    ; load val from xdata
    mov   dptr,#_dataout_PARM_2
    movx  a, @dptr

    ; restore dptr
    mov   dpl, r2
    mov   dph, r3

    ; write to the desired address
    movx  @dptr, a
  __endasm;
}

// writes val to the fixed address 0xFFFF
void debugout(char val)
{
  __asm
    mov   a, dpl          ; val stored in dpl initially
    mov   dptr, #0xFFFF   ; load in fixed debugport address
    movx  @dptr, a 
  __endasm;
}
