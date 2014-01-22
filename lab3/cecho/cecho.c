/* Code leveraged from http://www.keil.com/support/docs/685.htm for testing purposes. */
#include <at89c51ed2.h>
#include <stdio.h>

void putchar(char c) {
  while(!TI);   // spin until last character sent 

  TI = 0;       
  SBUF = c; 
} 

char getchar(void) {
  while(!RI);

  RI = 0;
  return SBUF;
}

void main (void)
{
  //piggyback off Paulmon's initialization
//  SCON  = 0x50;                   /* SCON: mode 1, 8-bit UART, enable rcvr    */
//  TMOD |= 0x20;                   /* TMOD: timer 1, mode 2, 8-bit reload      */
//  TH1   = 0xFD;                   /* TH1:  reload value for 9600 baud         */
//  TR1   = 1;                      /* TR1:  timer 1 run                        */
//  TI    = 0;                      /* TI:   set TI to send first char of UART  */

  while(1) {
    putchar(getchar());
  }
}
