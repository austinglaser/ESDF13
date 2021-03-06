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
CODE_LOC = 0x3000	# To work with Paulmon
#CODE_LOC = 0x0000
CODE_SIZE = 0x8000
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
ASM_FILES = $(wildcard $(SRC_DIR)/*.asm)
HDR_FILES = $(wildcard $(SRC_DIR)/*.h)

COBJ_FILES = $(addprefix $(BIN_DIR)/,$(notdir $(SRC_FILES:.c=.rel)))
AOBJ_FILES = $(addprefix $(BIN_DIR)/,$(notdir $(ASM_FILES:.asm=.rel)))
OBJ_FILES = $(COBJ_FILES) $(AOBJ_FILES)

# Flags for the compiler
CFLAGS = --opt-code-size -m$(DEVICE) --std-sdcc99 --model-$(MODEL) $(I_INCLUDE)

# Flags for the linker
LFLAGS = --model-$(MODEL) --out-fmt-ihx\
	 --code-loc $(CODE_LOC) --code-size $(CODE_SIZE)\
	 --xram-loc $(XRAM_LOC) --xram-size $(XRAM_SIZE)

# Main build target
all: bin/main.hex

debug: clean
debug: CFLAGS += -DDEBUG
debug: all

# Hex file
bin/main.hex: $(OBJ_FILES) $(HDR_FILES) Makefile
	@echo "Linking..."
	@$(CC) $(LFLAGS) $(OBJ_FILES) -o bin/main.hex

# Object files from c sources
$(COBJ_FILES): $(BIN_DIR)/%.rel: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	@echo "Compiling $< ---> $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# Object files from assembly sources
$(AOBJ_FILES): $(BIN_DIR)/%.rel: $(SRC_DIR)/%.asm $(SRC_DIR)/%.h
	@echo "Assembling $< ---> $@"
	@$(AS) $(CFLAGS) -c $< -o $@

# A phony target gets built no matter the status of dependencies
.PHONY: clean
clean:
	rm -rf bin/*
