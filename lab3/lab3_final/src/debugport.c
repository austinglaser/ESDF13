#include "debugport.h"

void dataout(char xdata * address, char val) 
{
  *address = val;
}
