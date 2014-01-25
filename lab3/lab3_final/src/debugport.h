#ifndef _DEBUGPORT_H_
#define _DEBUGPORT_H_

#ifdef DEBUG
#define DEBUGPORT(x) dataout(0xFF00, (x))
#else
#define DEBUGPORT(x)
#endif

void dataout(char xdata * address, char  val);

#endif
