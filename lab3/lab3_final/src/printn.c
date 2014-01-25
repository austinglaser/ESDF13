#include "printn.h"

// Prints 'val' to the serial port as a string, interpreted
// in base 'base'. 'n_digits' specifies the desired width
// of the number. When zero, the number has no padding.
// When it's a positive number, pads the value with zeroes until
// it reaches the desired width. Numbers which go above this width are
// NOT truncated
void printn(int val, int base, int n_digits)
{
  // 32 bytes is large enough to hold the representation
  // of any int number
  char str[32];
  char digit;
  char offset;

  // initialize output string to zeros
  int i;
  for (i = 0; i < 32; i++) str[i] = '0';

  // check for negative number; decrement the amount
  // of padding to account for the negative sign
  if (val < 0) {
    putchar('-');
    n_digits--;
  }

  // translate the number into a string
  for (i = 0; val; i++) {
    // calculate next digit (numerically)
    digit = abs(val % base);
    
    // Different offsets to account for possibility
    // of bases larget than 10 (hexadecimal especially)
    if (digit <= 9) offset = '0';
    else            offset = ('A' - 10);

    // put the correct ascii character in the string
    str[i] = digit + offset;

    // get ready for the next character
    val /= base;
  }

  // ensure something is printed if our value
  // is zero
  if (n_digits == 0 && i == 0) putchar('0');

  // We will read the string backwards. Move
  // i to a location further down if we need
  // more padding (remember, str was initially
  // zero-filled)
  if (n_digits > 0) {
    i = (n_digits < i) ? i : n_digits;
  }

  // print our final string
  for (i--; i >= 0; i--) {
    putchar(str[i]);
  }
}
