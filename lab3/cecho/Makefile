CC = sdcc

# information about code location and size
CODE_LOCATION = 0x4000
CODE_SIZE =			0x4000
XRAM_LOCATION = 0x0000
XRAM_SIZE =			0x4000

# put this info in sdcc's format
LOCATION_FLAGS = --code-loc $(CODE_LOCATION) --code-size $(CODE_SIZE) --xram-loc $(XRAM_LOCATION) --xram-size $(XRAM_SIZE)
# format of output files
FORMAT_FLAGS = -mmcs51 --model-large --out-fmt-ihx --std-sdcc99
# compiler behavior
BEHAVIOR_FLAGS = --opt-code-size --verbose

# Mash this all together
CFLAGS = $(BEHAVIOR_FLAGS) \
				 $(FORMAT_FLAGS) \
				 $(LOCATION_FLAGS)

all: cecho.ihx

cecho.ihx: cecho.rel
	$(CC) $(CFLAGS) cecho.rel -o cecho.ihx

cecho.rel: cecho.c
	$(CC) $(CFLAGS) -c cecho.c -o cecho.rel

clean:
	find -E . -regex './cecho.[a-z]{3}' -exec rm {} \;
#	rm -f cecho.lnk cecho.map cecho.rel cecho.sym cecho.asm cecho.ihx cecho.lst cecho.mem cecho.rst


