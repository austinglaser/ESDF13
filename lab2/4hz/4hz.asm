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

STARTUP     AJMP  T0_INIT         ; go to init routine (need to make space for ISR)

            ORG   $0100

T0_INIT     MOV   R2,#04H         ; count down from 4
            MOV   TH0,#e1H        ; init timer at E104h
            MOV   TL0,#04H
            MOV   TMOD,#01H       ; int clk,timer,16-bit (mode 1)
            SETB  IE.1            ; IE.1 = ET0. Enables timer 0 interrupt
            SETB  IE.7            ; IE.7 = EA. Enables interrupts
            SETB  TCON.4          ; TCON.4 = TR0. Turns on timer
WAIT        NOP                   ; idle loop
            CPL   P1.3
            SJMP  WAIT


; Interrupt. Generated with frequency 3600 Hz so
; routine counts number of calls and switches every
; 900.
;
; NOTE: This routine can ONLY be used as-is if
; other interrupts are not used. If they are,
; it's far safer to have a jump instruction 
; at the interrupt vector with the actual ISR 
; stored elsewhere in memory.

            ORG   $000B           ; timer zero interrupt vector is 000B.

ISR_T0      SETB  P1.2            ; signal interrupt begin
            MOV   TH0,#e1H        ; init timer at 0
            MOV   TL0,#04H        ; autoreload zero
            SETB  TCON.4          ; TCON.4 = TR0. Turns on timer
            DJNZ  R2,INT_DONE     ; count down from 4
            MOV   R2,#04H         ; re-init r2
            CPL   P1.1            ; toggle LED pin
INT_DONE    CLR   P1.2            ; signal interrupt end
            RETI                  ; continue waiting in main routine
