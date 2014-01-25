#include "getstring.h"

// reads a newline-terminated string
// into buffer. Reads at most buff_len - 1 characters.
// Guaranteed to null terminate the string either way
// Returns the address of the buffer
char * getstring(char * buff, int buff_len)
{
  int i;
  char c;

  // Can't read anything into a zero length buffer.
  if (buff_len <= 0 || !buff) return NULL;

  // Read at most buff_len - 1 characters
  for (i = 0; i < (buff_len - 1); i++) {
    // get a character, echo it to the serial
    // port. TODO: Implement backspace support
    c = getchar();
    putchar(c);

    // check if we see a terminating character
    if (c == '\n' || c == '\r') {
      if (c == '\r') putchar('\n');
      break;
    }

    // read character into the buffer
    buff[i] = c;
  }

  // null terminate
  buff[i] = '\0';

  return buff;
}
