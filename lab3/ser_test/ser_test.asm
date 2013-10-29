; Austin Glaser
; ESDF13
;
; Continuously transmits the letter 'U' on the serial port.
; Baud rate set to 9600

            ORG   $0000h

STARTUP     MOV   SCON,#40H       ; Mode 1: 8 bit UART. No receive right now.
            ORL   PCON,#70H       ; Use baud rate doubling (set PCON.7)
            MOV   TH1,#0FAH       ; Baud rate: 9600
            MOV   TMOD,#20H       ; timer 1: 8 bit autoreload (mode 2)
            SETB  TCON.6          ; Enable timer 1

TRANSMIT    MOV   SBUF,#'U'       ; Send the letter 'U'


WAIT        JNB   T1,WAIT         ; Wait till the last char is sent
            CLR   T1              ; Tell software to send next char
            AJMP  TRANSMIT        ; infinite loop
