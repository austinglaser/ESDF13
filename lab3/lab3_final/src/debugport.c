#include "debugport.h"

// simply writes a value to the specified address.
// Could be made more efficient with assembly
void dataout(char xdata * address, char val) 
{
  *address = val;
}
