#include "strtoi.h"

int ipow(int base, int exp);

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
    if ('0' <= str[i] && str[i] <= '9') result += (str[i] - '0') * ipow(10, (len - i - 1));
    else                                break;
  }
  // last unconverted character. Used to
  // check success of conversions (should
  // point to  '\0' when everything's done)
  *endptr = str + i;

  if (negative) result *= -1;

  return result;
}

// exponentiation by squaring, from:
// http://stackoverflow.com/questions/101439/the-most-efficient-way-to-implement-an-integer-based-power-function-powint-int
int ipow(int base, int exp)
{
  int result = 1;
  while (exp)
  {
    if (exp & 1)
      result *= base;
    exp >>= 1;
    base *= base;
  }

  return result;
}
