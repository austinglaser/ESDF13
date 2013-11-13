                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : FreeWare ANSI-C Compiler
                              3 ; Version 2.6.0 #4309 (May 20 2007)
                              4 ; This file generated Tue Nov 12 14:55:28 2013
                              5 ;--------------------------------------------------------
                              6 	.module c_test
                              7 	.optsdcc -mmcs51 --model-large
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _main
                             13 ;--------------------------------------------------------
                             14 ; special function registers
                             15 ;--------------------------------------------------------
                             16 	.area RSEG    (DATA)
                             17 ;--------------------------------------------------------
                             18 ; special function bits
                             19 ;--------------------------------------------------------
                             20 	.area RSEG    (DATA)
                             21 ;--------------------------------------------------------
                             22 ; overlayable register banks
                             23 ;--------------------------------------------------------
                             24 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                      25 	.ds 8
                             26 	.area REG_BANK_1	(REL,OVR,DATA)
   0008                      27 	.ds 8
                             28 ;--------------------------------------------------------
                             29 ; internal ram data
                             30 ;--------------------------------------------------------
                             31 	.area DSEG    (DATA)
                             32 ;--------------------------------------------------------
                             33 ; overlayable items in internal ram 
                             34 ;--------------------------------------------------------
                             35 	.area OSEG    (OVR,DATA)
                             36 ;--------------------------------------------------------
                             37 ; Stack segment in internal ram 
                             38 ;--------------------------------------------------------
                             39 	.area	SSEG	(DATA)
   0021                      40 __start__stack:
   0021                      41 	.ds	1
                             42 
                             43 ;--------------------------------------------------------
                             44 ; indirectly addressable internal ram data
                             45 ;--------------------------------------------------------
                             46 	.area ISEG    (DATA)
                             47 ;--------------------------------------------------------
                             48 ; bit data
                             49 ;--------------------------------------------------------
                             50 	.area BSEG    (BIT)
                             51 ;--------------------------------------------------------
                             52 ; paged external ram data
                             53 ;--------------------------------------------------------
                             54 	.area PSEG    (PAG,XDATA)
                             55 ;--------------------------------------------------------
                             56 ; external ram data
                             57 ;--------------------------------------------------------
                             58 	.area XSEG    (XDATA)
                             59 ;--------------------------------------------------------
                             60 ; external initialized ram data
                             61 ;--------------------------------------------------------
                             62 	.area XISEG   (XDATA)
                             63 	.area HOME    (CODE)
                             64 	.area GSINIT0 (CODE)
                             65 	.area GSINIT1 (CODE)
                             66 	.area GSINIT2 (CODE)
                             67 	.area GSINIT3 (CODE)
                             68 	.area GSINIT4 (CODE)
                             69 	.area GSINIT5 (CODE)
                             70 	.area GSINIT  (CODE)
                             71 	.area GSFINAL (CODE)
                             72 	.area CSEG    (CODE)
                             73 ;--------------------------------------------------------
                             74 ; interrupt vector 
                             75 ;--------------------------------------------------------
                             76 	.area HOME    (CODE)
   3000                      77 __interrupt_vect:
   3000 02 30 26             78 	ljmp	__sdcc_gsinit_startup
   3003 32                   79 	reti
   3004                      80 	.ds	7
   300B 32                   81 	reti
   300C                      82 	.ds	7
   3013 32                   83 	reti
   3014                      84 	.ds	7
   301B 32                   85 	reti
   301C                      86 	.ds	7
   3023 02 30 C3             87 	ljmp	_serial_interrupt_handler
                             88 ;--------------------------------------------------------
                             89 ; global & static initialisations
                             90 ;--------------------------------------------------------
                             91 	.area HOME    (CODE)
                             92 	.area GSINIT  (CODE)
                             93 	.area GSFINAL (CODE)
                             94 	.area GSINIT  (CODE)
                             95 	.globl __sdcc_gsinit_startup
                             96 	.globl __sdcc_program_startup
                             97 	.globl __start__stack
                             98 	.globl __mcs51_genXINIT
                             99 	.globl __mcs51_genXRAMCLEAR
                            100 	.globl __mcs51_genRAMCLEAR
                            101 	.area GSFINAL (CODE)
   307F 02 30 82            102 	ljmp	__sdcc_program_startup
                            103 ;--------------------------------------------------------
                            104 ; Home
                            105 ;--------------------------------------------------------
                            106 	.area HOME    (CODE)
                            107 	.area CSEG    (CODE)
   3082                     108 __sdcc_program_startup:
   3082 12 30 87            109 	lcall	_main
                            110 ;	return from main will lock up
   3085 80 FE               111 	sjmp .
                            112 ;--------------------------------------------------------
                            113 ; code
                            114 ;--------------------------------------------------------
                            115 	.area CSEG    (CODE)
                            116 ;------------------------------------------------------------
                            117 ;Allocation info for local variables in function 'main'
                            118 ;------------------------------------------------------------
                            119 ;------------------------------------------------------------
                            120 ;	c_test.c:3: int main(void) {
                            121 ;	-----------------------------------------
                            122 ;	 function main
                            123 ;	-----------------------------------------
   3087                     124 _main:
                    0002    125 	ar2 = 0x02
                    0003    126 	ar3 = 0x03
                    0004    127 	ar4 = 0x04
                    0005    128 	ar5 = 0x05
                    0006    129 	ar6 = 0x06
                    0007    130 	ar7 = 0x07
                    0000    131 	ar0 = 0x00
                    0001    132 	ar1 = 0x01
                            133 ;	c_test.c:4: serial_init();
                            134 ;	genCall
   3087 12 30 92            135 	lcall	_serial_init
                            136 ;	c_test.c:5: while (1) {
   308A                     137 00102$:
                            138 ;	c_test.c:6: serial_putc('U');
                            139 ;	genCall
   308A 75 82 55            140 	mov	dpl,#0x55
   308D 12 31 2A            141 	lcall	_serial_putc
                            142 ;	Peephole 112.b	changed ljmp to sjmp
   3090 80 F8               143 	sjmp	00102$
                            144 ;	Peephole 259.a	removed redundant label 00104$ and ret
                            145 ;
                            146 	.area CSEG    (CODE)
                            147 	.area CONST   (CODE)
                            148 	.area XINIT   (CODE)
