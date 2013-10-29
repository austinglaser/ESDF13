; Austin Glaser
; ESDF13
;
; Echoes what's received on serial port
; Baud rate set to 19200

            ORG   $0000

GOTO_START  AJMP  STARTUP         ; don't overwrite interrupt vectors

            ORG   $0100

STARTUP     MOV   SCON,#50H       ; mode 1: 8 bit UART. REN = 1
            ORL   PCON,#80H       ; Double baud rate
            MOV   TH1,#0FDH       ; Baud rate: 19200
            MOV   TMOD,#20H       ; timer 1: 8 bit autoreload (mode 2)
            SETB  TCON.6          ; Enable timer 1

WAITR       JNB   RI,WAITR        ; wait till character is recieved
            CLR   TI              ; immediately send what's in the buffer

WAITT       JNB   TI,WAITT        ; Wait for byte to be transmitted            
            SJMP  WAITR           ; continue waiting for recieve
