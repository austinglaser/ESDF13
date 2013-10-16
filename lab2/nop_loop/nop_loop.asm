; nop loop for testing purposes

          ORG $0000
LOOP      NOP
          CPL P1.1
          AJMP LOOP
