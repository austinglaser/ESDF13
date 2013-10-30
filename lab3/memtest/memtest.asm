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

MAIN      MOV   SCON,#50H       ; mode 1: 8 bit UART. REN = 1
          ORL   PCON,#80H       ; Double baud rate
          MOV   TH1,#0FDH       ; Baud rate: 19200
          MOV   TMOD,#20H       ; timer 1: 8 bit autoreload (mode 2)
          SETB  TCON.6          ; Enable timer 1
          ANL   SCON,#0FCH      ; Clear TI and RI

TEST_BOT  MOV   DPTR,#0400h     ; Test bottom of memory
          ACALL TEST_MEM
          CJNE  A,#00h,FAIL_BOT ; simply end on failure
          AJMP  TEST_TOP        ; move on to next test

FAIL_BOT  MOV   A,#'B'          ; send 'B' to indicate where failed
          ACALL SEND_CHAR

TEST_TOP  MOV   DPTR,#07FFFh    ; Test top
          ACALL TEST_MEM
          CJNE  A,#00h,FAIL_TOP ; simply end on failure
          AJMP  TEST_MID        ; move on to next test

FAIL_TOP  MOV   A,#'T'          ; send 'B' to indicate where failed
          ACALL SEND_CHAR

TEST_MID  MOV   DPTR,#0400h     ; Test middle of memory
          ACALL TEST_MEM
          CJNE  A,#00h,FAIL_BOT ; go to failure
          AJMP  SEND_SUC        ; indicate success

FAIL_MID  MOV   A,#'M'          ; send 'B' to indicate where failed
          ACALL SEND_CHAR

          AJMP  SPIN            ; keep spinning

SEND_SUC  MOV   A,#'S'          ; Send success signal
          ACALL SEND_CHAR

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
          SJMP  END_MEM         ; Finish

FAIL      MOV   A,#01h          ; it didn't work...

END_MEM   RET


; sends the character in the accumulator on serial

SEND_CHAR JNB   SCON.1,SEND_CHAR ; wait for bit to finish sending
          MOV   SBUF,A          ; put it in the buffer
          CLR   SCON.1          ; Indicate send

END_SER   RET
