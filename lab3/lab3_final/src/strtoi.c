#include "strtoi.h"

// private function which calculates
// the integer power of base^exp
// through repeated squaring.
//
// It would also have been reasonable to do this
// by using a lookup table
// 
// From:
// http://stackoverflow.com/questions/101439/the-most-efficient-way-to-implement-an-integer-based-power-function-powint-int
int ipow(int base, int exp);

// Parses 'str' and looks for a decimal value, which is then returned. 
// 'endptr' will point towards the last unconverted character on return. 
// For successful, full conversions this should be the null terminator 
// and the string should be nonempty. 
// 
// Based of the specification for strtol(), an unimplemented c library 
// routine.  
// 
// TODO: Add support for multiple bases
int strtoi(char const * str, char ** endptr){
  int result = 0;
  int negative = 0;
  int i;
  int len = strlen(str);

  // check for a negative value
  if (str[0] == '-') {
    negative = 1;
    
    // Without this check, an input of
    // "-" would be considered valid
    if (str[1] == '\0' ) {
      *endptr = str;
      return 0;
    }

    // move to next character, decrement the length
    // to only account for the numerical characters
    str++;
    len--;
  }

  // loop through all characters
  for (i = 0; str[i]; i++) {
    // if it's numeric, add it to the sum
    // For the ith most significant digit,
    // we add (digit)*(10^i). Since we read
    // from msb to lsb, we calculate the power
    // starting from high to low
    if ('0' <= str[i] && str[i] <= '9') result += (str[i] - '0') * ipow(10, (len - i - 1));
    else                                break;
  }
  // last unconverted character. Used to
  // check success of conversions (should
  // point to  '\0' when successful)
  *endptr = str + i;

  // negate the result if we found an initial '-'
  if (negative) result *= -1;

  return result;
}

// private function which calculates
// the integer power of base^exp
// through repeated squaring.
//
// It would also have been reasonable to do this
// by using a lookup table since we currently
// only need base 10 powers
//
// From: (with added comments)
// http://stackoverflow.com/questions/101439/the-most-efficient-way-to-implement-an-integer-based-power-function-powint-int
int ipow(int base, int exp)
{
  int result = 1;
  // This works because:
  // x^n = ((x^2)^(n/2)) * (x^(n%2))
  // the last term will add an extra 'x' when
  // n is odd.
  
  // iterate while exp isn't zero
  while (exp)
  {
    // if the exponent is odd, we have to add one more
    // multiplication of the base to the result
    if (exp & 1) result *= base;

    // divide the exponent by 2
    exp >>= 1;

    // square the base
    // the check removes a reduntant multiplication
    // (if exp = 1 on entry, the loop is done and we
    // simply need to return result
    if (exp) base *= base;
  }

  return result;
}
