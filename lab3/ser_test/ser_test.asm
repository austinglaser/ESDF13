; Austin Glaser
; ESDF13
;
; Continuously transmits the letter 'U' on the serial port.
; Baud rate set to 9600
;
; Based off code found at http://www.freewebs.com/maheshwankhede/rs232.html

            ORG   $0000

GOTO_START  AJMP STARTUP          ; Make sure we don't overwrite int vectors

            ORG   $0100

STARTUP     MOV   SCON,#50H       ; Mode 1: 8 bit UART. REN = 1
            ANL   PCON,#7FH       ; turn off baud rate doubling
            MOV   TH1,#0FDH       ; Baud rate: 9600
            MOV   TMOD,#20H       ; timer 1: 8 bit autoreload (mode 2)
            SETB  TCON.6          ; Enable timer 1

TRANSMIT    MOV   SBUF,#'U'       ; Send the letter 'U'

            MOV   R3,#0FFH         
DELAY_OUT   MOV   R2,#0FFH         ; add some space between characters
DELAY_IN    DJNZ  R2,DELAY_IN
            DJNZ  R3,DELAY_OUT


WAIT        JNB   SCON.1,WAIT     ; Wait till the last char is sent (SCON.1 = TI)
            CLR   SCON.1          ; Tell hardware to send next char
            SJMP  TRANSMIT        ; infinite loop
