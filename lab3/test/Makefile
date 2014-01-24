#####################################################################
#	Makefile for ECEN 4613 projects
#	Author:		Austin Glaser
#	Class:		ECEN 4613
#	License:	GNU lesser general public license
#####################################################################

# Compile using sdcc
CC = sdcc
AS = asx8051

# Directory Structure
PROJ_DIR = .
SRC_DIR = $(PROJ_DIR)/src
BIN_DIR = $(PROJ_DIR)/bin

# Define sdcc's home directory
SDCC = /usr/local/share/sdcc

# Configure project (memory model, device, memory map)
DEVICE = mcs51
MODEL = large
CODE_LOC = 0x6000	# To work with Paulmon
#CODE_LOC = 0x0000
CODE_SIZE = 0x2000
XRAM_LOC = 0x0000
XRAM_SIZE = 0x8000

# Where we look for header files
SDCC_INC = $(SDCC)/include/
DEVICE_INC = $(SDCC_INC)/$(DEVICE)/
INCLUDE = $(SDCC_INC) $(DEVICE_INC) $(LOC_INC)

# Convert header file locations into an argument format
# by adding prefix '-I'
I_INCLUDE = $(addprefix -I,$(dir $(INCLUDE)))

# Find local source files, generate list of objects
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(addprefix $(BIN_DIR)/,$(notdir $(SRC_FILES:.c=.rel)))

# Flags for the compiler
CFLAGS = --opt-code-size -m$(DEVICE) --std-sdcc99 --model-$(MODEL) $(I_INCLUDE)

# Flags for the linker
LFLAGS = --model-$(MODEL) --out-fmt-ihx\
	 --code-loc $(CODE_LOC) --code-size $(CODE_SIZE)\
	 --xram-loc $(XRAM_LOC) --xram-size $(XRAM_SIZE)

# Main build target
all: bin/main.hex

# Hex file
bin/main.hex: $(OBJ_FILES)
	@echo "Linking..."
	@$(CC) $(LFLAGS) $(OBJ_FILES) -o bin/main.hex

# Object files (TODO: Make more general. See ARM stuff)
$(OBJ_FILES): $(BIN_DIR)/%.rel: $(SRC_DIR)/%.c
	@echo "Compiling $< ---> $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# A phony target gets built no matter the status of dependencies
.PHONY: clean
clean:
	rm -rf bin/*
