#####################################################################
#	Makefile for ECEN 4613 projects
#	Author:		Austin Glaser
#	Class:		ECEN 4613
#	License:	GNU lesser general public license
#####################################################################

# Compile using sdcc
CC = sdcc

# Define sdcc's home directory
SDCC = /usr/local/share/sdcc

# Configure project (memory model, device, memory map)
DEVICE = mcs51
MODEL = large
#CODE_LOC = 0x3000	# To work with Paulmon
CODE_LOC = 0x0000
CODE_SIZE = 0x8000
XRAM_LOC = 0x0000
XRAM_SIZE = 0x8000

# Where we look for header files
SDCC_INC = $(SDCC)/include
DEVICE_INC = $(SDCC_INC)/$(DEVICE)
INCLUDE = $(SDCC_INC) $(DEVICE_INC)

# Convert header file locations into an argument format
# by adding prefix '-I'
I_INCLUDE = $(addprefix -I,$(dir $(INCLUDE)))

# Flags for the compiler
CFLAGS = --opt-code-size -m$(DEVICE) --std-sdcc99 --verbose --model-$(MODEL) $(I_INCLUDE)

# Flags for the linker
LFLAGS = --model-$(MODEL) --out-fmt-ihx\
	 --code-loc $(CODE_LOC) --code-size $(CODE_SIZE)\
	 --xram-loc $(XRAM_LOC) --xram-size $(XRAM_SIZE)

# Main build target
all: cpintog.ihx

# Hex file
cpintog.ihx: cpintog.rel
	sdcc $(LFLAGS) cpintog.rel -o cpintog.ihx

# Object files (TODO: Make more general. See ARM stuff)
cpintog.rel: cpintog.c
	sdcc $(CFLAGS) -c cpintog.c -o cpintog.rel

# A phony target gets built no matter the status of dependencies
.PHONY: clean
clean:
	rm -rf *.rel *.lst *.rst *.mem *.map *.sym *.lnk *.ihx *.asm
