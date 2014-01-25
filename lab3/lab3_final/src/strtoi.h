#ifndef _STRTOI_H_
#define _STRTOI_H_

#include <string.h>

// Parses 'str' and looks for a decimal value, which is then returned.
// 'endptr' will point towards the last unconverted character on return.
// For successful, full conversions this should be the null terminator
// and the string should be nonempty.
//
// Based of the specification for strtol(), an unimplemented c library
// routine. 
//
// TODO: Add support for multiple bases
int strtoi(char const * str, char ** endptr);

#endif
