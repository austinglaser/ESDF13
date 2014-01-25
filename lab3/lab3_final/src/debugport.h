#ifndef _DEBUGPORT_H_
#define _DEBUGPORT_H_

// Writes 'x' to an unused address (FFFFh).
// Only functional when DEBUG defined
#ifdef DEBUG
#define DEBUGPORT(x) dataout(0xFFFF, (x))
#else
#define DEBUGPORT(x)
#endif

// Writes the value to the specified xdata address
void dataout(char xdata * address, char  val);

#endif
