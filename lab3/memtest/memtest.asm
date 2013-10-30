; memtest.asm
; Austin Glaser
; ESDF13
;
; Tests access to NVRAM in address range 0400-7FFF
; If test is successful, writes a low value to the P1.1
; (LED pin). Otherwise, writes a high value.

          ORG   $0000

STARTUP   AJMP  MAIN


          ORG   $0100

MAIN      
T0_INIT   MOV   R2,#02H         ; count down from 2
          MOV   TH0,#1EH        ; init timer at 1EFCh
          MOV   TL0,#0FCH
          MOV   TMOD,#01H       ; int clk,timer,16-bit (mode 1)
          SETB  IE.1            ; IE.1 = ET0. Enables timer 0 interrupt
          SETB  IE.7            ; IE.7 = EA. Enables interrupts
          SETB  TCON.4          ; TCON.4 = TR0. Turns on timerV

SER_INIT  MOV   SCON,#50H       ; mode 1: 8 bit UART. REN = 1
          ORL   PCON,#80H       ; Double baud rate
          MOV   TH1,#0FDH       ; Baud rate: 19200
          MOV   TMOD,#20H       ; timer 1: 8 bit autoreload (mode 2)
          SETB  TCON.6          ; Enable timer 1
          ANL   SCON,#0FCH      ; Clear TI and RI

TEST_BOT  MOV   DPTR,#0400h     ; Test bottom of memory
          ACALL TEST_MEM
          CJNE  A,#00h,FAIL_BOT ; go to failure
          AJMP  TEST_TOP        ; move on to nest test

FAIL_BOT  MOV   A,#'B'          ; send 'B' to indicate where failed
          ACALL SEND_CHAR
          AJMP  SPIN            ; keep spinning

TEST_TOP  MOV   DPTR,#07FFFh    ; Test top
          ACALL TEST_MEM
          CJNE  A,#00h,FAIL_TOP ; go to failure
          AJMP  TEST_TOP        ; move on to nest test

FAIL_TOP  MOV   A,#'T'          ; send 'B' to indicate where failed
          ACALL SEND_CHAR
          AJMP  SPIN            ; keep spinning

TEST_MID  MOV   DPTR,#0400h     ; Test middle of memory
          ACALL TEST_MEM
          CJNE  A,#00h,FAIL_BOT ; go to failure
          AJMP  TEST_TOP        ; move on to nest test

FAIL_MID  MOV   A,#'M'          ; send 'B' to indicate where failed
          ACALL SEND_CHAR
          AJMP  SPIN            ; keep spinning

LED_ON    CLR   TCON.4          ; turn off blinking when successful
          CLR   IE.7
          CLR   IE.1
          CLR   P1.1            ; turn on LED

SPIN      SJMP  SPIN            ; spin when all done



; routine which writes several values to the memory
; pointed to by DPTR. Writes a low value to ACC
; if successful; otherwise writes high

TEST_MEM  MOV   A,#0FFh         ; Write FF
          MOVX  [DPTR],A        ; put in
          MOVX  A,[DPTR]        ; take out
          CJNE  A,#0FFh,FAIL    ; Failure

          MOV   A,#2Ah          ; Write 00
          MOVX  [DPTR],A        ; put in
          MOVX  A,[DPTR]        ; take out
          CJNE  A,#2Ah,FAIL     ; Failure

          MOV   A,#00h          ; Write 00
          MOVX  [DPTR],A        ; put in
          MOVX  A,[DPTR]        ; take out
          CJNE  A,#00h,FAIL     ; Failure

SUCCESS   MOV   A,#00h          ; It worked!
          SJMP  END             ; Finish

FAIL      MOV   A,#01h          ; it didn't work...

END       RET

; sends the character in the accumulator on serial

SEND_CHAR JNB   SCON.1,SEND_CHAR ; wait for bit to finish sending
          MOV   SBUF,A          ; put it in the buffer
          CLR   SCON.1          ; Indicate send

          RET

; Interrupt. Generated with frequency 16 Hz so
; routine counts number of calls and switches every
; 4.
;
; NOTE: This routine can ONLY be used as-is if
; other interrupts are not used. If they are,
; it's far safer to have a jump instruction 
; at the interrupt vector with the actual ISR 
; stored elsewhere in memory.

          ORG   $000B           ; timer zero interrupt vector is 000B.

ISR_T0    SETB  P1.2            ; signal interrupt begin
          MOV   TH0,#1EH        ; init timer at 1EFCh
          MOV   TL0,#0FCH
          SETB  TCON.4          ; TCON.4 = TR0. Turns on timer
          DJNZ  R2,INT_DONE     ; count down from 2
          MOV   R2,#02H         ; re-init r2
          CPL   P1.1            ; toggle LED pin
INT_DONE  CLR   P1.2            ; signal interrupt end
          RETI                  ; continue waiting in main routine
