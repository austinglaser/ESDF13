#ifndef _STRTOI_H_
#define _STRTOI_H_

// no implementation of strtol in stdlib, so I'm making my own
// (functionality similar but not identical to the library function)
// In particular, this doesn't use a flexible base.
// endptr points to the last unconverted character on return,
// providing a way to test the validity of conversions.
int strtoi(char const * str, char ** endptr);

#endif
