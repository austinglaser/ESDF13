; Attach LED driver circuit to P1.1
; Program blinks LED at 4 hz using
; an ISR to provide signal
; --------------------------------
; Author: Austin Glaser
; Date:   10/12/2013
; Class:  ESDF13


; Initialization routine. Sets up timer0 and registers
; for 4 Hz signal generation.
; Internal oscillator: 11.0592 MHz
; Internal Clock: osc/12 = 921.6 kHz
; 8 bit autoreload counts to 256,generating interrupts
; with frequency 3.6 kHz.
; To get 4 Hz,we must switch every 900 interrupts
; by decrementing two registers (initialized to 9 and 100
; respectively)

            ORG   $0000           ; Startup routine at 0000h

T0_INIT     MOV   R2,#64H         ; count down from 100
            MOV   R3,#09H         ; count down from 9 (*100 = 900)
            MOV   TH0,#00H        ; init timer at 0
            MOV   TL0,#00H        ; autoreload zero
            MOV   TMOD,#02H       ; int clk,timer,8-bit autoreload (mode 2)
            SETB  TCON.4          ; 8Bh = TCON.4 = TR0. Turns on timer
WAIT        SJMP  WAIT


; Interrupt. Generated with frequency 3600 Hz so
; routine counts number of calls and switches every
; 900.
;
; NOTE: This routine can ONLY be used as-is if
; other interrupts are not used. If they are,
; it's far safer to have a jump instruction at the interrupt vector with
; the actual ISR stored elsewhere in memory.

            ORG   $000B           ; timer zero interrupt vector is 000B.

ISR_T0      SETB  P1.2            ; signal interrupt begin
            DJNZ  R2,INT_DONE     ; count down from 100
            MOV   R2,#64H         ; re-init r2
            DJNZ  R3,INT_DONE     ; count down from 9 (*100)
            MOV   R2,#09H         ; re-init r3
            CPL   P1.1            ; toggle LED pin
INT_DONE    CLR   P1.2            ; signal interrupt end
            RETI                  ; continue waiting in main routine
