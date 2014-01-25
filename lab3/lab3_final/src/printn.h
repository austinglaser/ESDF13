#ifndef _PRINTN_H_
#define _PRINTN_H_

#include "putchar.h"
#include <stdio.h>
#include <stdlib.h>

// Prints 'val' to the serial port as a string, interpreted
// in base 'base'. 'n_digits' specifies the desired width
// of the number. When zero, the number has no padding.
// When it's a positive number, pads the value with zeroes until
// it reaches the desired width. Numbers which go above this width are
// NOT truncated
void printn(int val, int base, int n_digits);

#endif
