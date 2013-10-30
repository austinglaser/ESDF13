; memtest.asm
; Austin Glaser
; ESDF13
;
; Tests access to NVRAM in address range 0400-7FFF
; If test is successful, writes a low value to the P1.1
; (LED pin). Otherwise, writes a high value.

          ORG   $0000

STARTUP   SETB  P1.1            ; turn off LED

TEST_BOT  MOV   DPTR,#0400h     ; Test bottom of memory
          ACALL  TEST_MEM
          CJNE  A,#01h,SPIN     ; simply end on failure

TEST_TOP  MOV   DPTR,#07FFFh    ; Test top
          ACALL  TEST_MEM
          CJNE  A,#01h,SPIN     ; simply end on failure

TEST_MID  MOV   DPTR,#0400h     ; Test middle of memory
          ACALL  TEST_MEM
          CJNE  A,#01h,SPIN     ; simply end on failure

SUCCESS   CLRB  P1.1            ; turn LED on when successful

SPIN      SJMP  SPIN            ; spin when all done



; routine which writes several values to the memory
; pointed to by DPTR. Writes a low value to ACC
; if successful; otherwise writes high
          ORG   $0100

TEST_MEM  MOVX  [DPTR],#0FFh    ; Write FF to memory
          MOVX  A,[DPTR]        ; read byte back
          CJNE  A,#0FFh,FAIL    ; Failure

          MOVX  [DPTR],#00h     ; Write FF to memory
          MOVX  A,[DPTR]        ; read byte back
          CJNE  A,#00h,FAIL     ; Failure

SUCCESS   MOV   A,#00h          ; It worked!
          SJMP  END             ; Finish

FAIL      MOV   A,#01h          ; it didn't work...

END       RET
