#include "main.h"

extern unsigned char xdata heap[HEAP_SIZE];

void setup(void);
void get_buffers(void);
void hexdump(char const * buffer, int len);

#define MAX_INPUT_LEN 128

// user inputed length of buffer
long buff_len;

//pointers to heap-allcoated memory
char xdata * buffer0;
char xdata * buffer1;

int main(void)
{
  int numberof[256];
  int i;
  char c;
  int n_chars = 0;
  int n_stored = 0;

  // initialize heap
  setup();

  // prompt user for size, allocate buffers.
  // Blocks while waiting for correct input
  get_buffers();

  // print instructions
  printf("Enter characters for storage.\n");
  printf("\t=\thex dump of buffer contents\n");
  printf("\t?\tprint stats and clear buffer\n");

  // store the number of occurrences of each ascii character
  for (i = 0; i < 256; i++) {
    numberof[i] = 0;
  }

  while(1) {
    // get a character (getchar() echoes)
    c = getchar();


    // log the character
    n_chars++;
    numberof[c]++;
    
    // is it a storage character?
    if ( ('0' <= c && c <= '9') ||
         ('a' <= c && c <= 'z') ||
         ('A' <= c && c <= 'Z') ) {

      // if so, and we have room, store it
      if (n_stored < buff_len) {
        buffer0[n_stored] = c;
        n_stored++;
      }
    }

    // flush?
    if (c == '?') {
      // print general stats
      printf("\nStored %d characters in buffer0, with %d free\n", n_stored, buff_len - n_stored);
      printf("Buffer 0: %d bytes at %x\n", buff_len, buffer0);
      printf("Buffer 1: %d bytes at %x\n\n", buff_len/4, buffer1);

      // print specific letter stats
      // 0-9
      for (c = '0'; c <= '9'; c++) {
        printf("%c-%d ", c, numberof[c]);
        numberof[c] = 0;
      }
      // FEMA
      printf("\n");
      printf("F-%d ", 'F', numberof['F']); numberof['F'] = 0;
      printf("E-%d ", 'E', numberof['E']); numberof['E'] = 0;
      printf("M-%d ", 'M', numberof['M']); numberof['M'] = 0;
      printf("A-%d ", 'A', numberof['A']); numberof['A'] = 0;
      printf("\n");


      // clear buffer, printing to screen
      printf("Flushing buffer...");
      for (i = 0; i < n_stored; i++) {
        if (i % 50 == 0) printf("\n");
        printf("%c", buffer0[i]);
      }
      printf("\n\n");

      // actually clear buffer
      n_stored = 0;
      n_chars = 0;
    }

    // report?
    if (c == '=') {
      hexdump(buffer0, n_stored);
      printf("\n");
    }
  }
}

void setup(void)
{
  // enable 1024 bytes of XRAM
  AUXR |= 0x0C;

  // initialize heap
  malloc_setup();
}

void get_buffers(void) {
  // buffer for getstring input
  char string_buffer[MAX_INPUT_LEN];

  // points to last unconverted char from strtol()
  // If this is the null terminator in any but an
  // empty string, we know conversion was successful.
  char * endptr;

  while (1) {
    // user prompt, get their string
    printf("Enter your buffer size ( 24 <= n <= 1600, n a multiple of 8): ");
    getstring(string_buffer, MAX_INPUT_LEN);

    // attempt to convert to integer
    buff_len = strtoi(string_buffer, &endptr);

    //check for conversion validity
    if (*string_buffer == '\0' || *endptr != '\0')  printf("\nNon-integer input.\n");
    else if (buff_len < 24 || buff_len > 1600)      printf("\nValue out of range [24 1600].\n", buff_len);
    else if (buff_len % 8 != 0)                     printf("\nValue must be divisible by 8.\n", buff_len);
    else {
      // attempt to allocate buffers
      buffer0 = malloc(buff_len);
      buffer1 = malloc(buff_len/4);

      // check success
      if (!buffer0 || !buffer1) {
        if (buffer0) free(buffer0);
        if (buffer1) free(buffer1); //this is probably pedantic, but we'll leave it in anyway
        printf("\nAllocation failure.\n");
      }
      else break; // everything went well!
    }
  }
}

void hexdump(char const * buffer, int len)
{
  int i;
  printf("      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

  for (i = 0; i < len; i++) {
    if (i % 16 == 0) printf("\n%2.4X: ", (buffer + i));
    printf("%2.2X ", buffer[i]);
  }
  printf("\n");
}
