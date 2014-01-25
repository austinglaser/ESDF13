#ifndef _PUTCHAR_H_
#define _PUTCHAR_H_

#include <at89c51ed2.h>

// Puts out_c in the uart and queues for transmission.
// Keeps track of characters printed since the last newline
// (used for 'finish_line')
void putchar(char out_c);


// Places the character 'term' at least 'len' characters into the line
// (zero based). Makes use of the fact that putchar records
// how many characters it has already printed this line.
// Useful for drawing boxes, where you want the right side to be
// justified without necessarily knowing the number of characters on
// a particular line before runtime
void finish_line(char term, int len);

#endif
