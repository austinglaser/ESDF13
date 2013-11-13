/* Code leveraged from http://www.keil.com/support/docs/685.htm for testing purposes. */
#include <8051.h>
#include <stdio.h>

void putc(unsigned char c) {
  while(!TI);   /* spin until last character sent */

  SBUF = c;     /* put the next char in the buffer */
  TI = 0;       /* send it */
}

/*unsigned char getc(void) {
  while(!RI);

  unsigned char c;
  c = SBUF;
  RI = 0;
  return c;
} */

void main (void)
{
  SCON  = 0x50;                   /* SCON: mode 1, 8-bit UART, enable rcvr    */
  TMOD |= 0x20;                   /* TMOD: timer 1, mode 2, 8-bit reload      */
  TH1   = 0xFD;                   /* TH1:  reload value for 9600 baud         */
  TR1   = 1;                      /* TR1:  timer 1 run                        */
  TI    = 1;                      /* TI:   set TI to send first char of UART  */

  while(1)
  {
    putc('U');
  }
}
