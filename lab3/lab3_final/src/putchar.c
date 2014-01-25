#include "putchar.h"

int n_online = 0;

// Puts out_c in the uart and queues for transmission.
// Keeps track of characters printed since the last newline
// (used for 'finish_line')
void putchar(char out_c)
{
  // If we want a newline,
  // we have to print two characters:
  // carriage return and newline. This
  // is also where we reset the character count
  if (out_c == '\n' || out_c == '\r') {
    out_c = '\n';

    // block until previous character is transmitted
    while (!TI);

    // send a linefeed
    TI = 0;
    SBUF = '\r';

    // reset character count
    n_online = 0;
  }


  // block until previous character is transmitted
  while (!TI);

  // send the character
  TI = 0;
  SBUF = out_c;

  // increment out count
  n_online++;
}

// Places the character 'term' at least 'len' characters into the line
// (zero based). Makes use of the fact that putchar records
// how many characters it has already printed this line.
// Useful for drawing boxes, where you want the right side to be
// justified without necessarily knowing the number of characters on
// a particular line before runtime
void finish_line(char term, int len)
{
  int i;

  // calculate how much padding we need
  // (this value will be negative
  // if we've already overrun the desired
  // length)
  int padding = len - n_online;

  // print padding (runs zero times if 
  // padding <= 0
  for (i = 0; i < padding; i++) putchar(' ');


  // print terminating character
  putchar(term);
}
