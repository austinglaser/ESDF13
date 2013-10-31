; Austin Glaser
; ESDF13
;
; Echoes what's received on serial port
; Baud rate set to 9600

            ORG   $0000

GOTO_START  AJMP  STARTUP         ; don't overwrite interrupt vectors

            ORG   $0100

STARTUP     MOV   SCON,#50H       ; mode 1: 8 bit UART. REN = 1
            ANL   PCON,#7FH       ; no baud rate doubling
            MOV   TH1,#0FDH       ; Baud rate: 9600
            MOV   TMOD,#20H       ; timer 1: 8 bit autoreload (mode 2)
            SETB  TCON.6          ; Enable timer 1
            ANL   SCON,#0FCH      ; Clear TI and RI

WAITR       JNB   SCON.0,WAITR    ; wait till character is recieved
            CLR   SCON.0          ; clear RI; acknowledge receipt
            CLR   SCON.1          ; immediately send what's in the buffer

WAITT       JNB   SCON.1,WAITT    ; Wait for byte to be transmitted            
            SJMP  WAITR           ; continue waiting for recieve
