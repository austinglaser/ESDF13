#ifndef _DEBUGPORT_H_
#define _DEBUGPORT_H_

#ifdef DEBUG
#define DEBUGPORT(x) dataout(0xFFFF, (x))
#else
#define DEBUGPORT(x)
#endif

void dataout(void xdata * address, char val);

#endif
