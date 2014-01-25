#ifndef _GETSTRING_H_
#define _GETSTRING_H_

#include "getchar.h"
#include "putchar.h"
#include <stdlib.h>

// reads a newline-terminated string
// into buffer. Reads at most buff_len - 1 characters.
// Guaranteed to null terminate the string either way
// Returns the address of the buffer
char * getstring(char * buff, int buff_len);

#endif
