#include "main.h"

extern unsigned char xdata heap[HEAP_SIZE];

void setup(void);
void get_buffers(void);

#define MAX_INPUT_LEN 128

// user inputed length of buffer
long buff_len;

//pointers to heap-allcoated memory
char xdata * buffer0;
char xdata * buffer1;

int main(void)
{
  // initialize heap
  setup();

  // prompt user for size, allocate buffers.
  // Blocks while waiting for correct input
  get_buffers();

  printf("buffer0: %d bytes at %x\n", buff_len, buffer0);
  printf("buffer1: %d bytes at %x\n", buff_len/4, buffer1);

  while(1);
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
  char * endptr;

  while (1) {
    // user prompt, get their string
    printf("Enter your buffer size ( 24 <= n <= 1600, n a multiple of 8): ");
    getstring(string_buffer, MAX_INPUT_LEN);

    // attempt to convert to integer
    buff_len = strtoi(string_buffer, &endptr);

    //check for conversion validity
    if (*string_buffer == '\0' || *endptr != '\0')  printf("Non-integer input.\n");
    else if (buff_len < 24 || buff_len > 1600)      printf("Value out of range (%d).\n", buff_len);
    else if (buff_len % 8 != 0)                     printf("Value must be divisible by 8 (%d).\n", buff_len);
    else {
      // attempt to allocate buffers
      buffer0 = malloc(buff_len);
      buffer1 = malloc(buff_len/4);

      // check success
      if (!buffer0 || !buffer1) {
        if (buffer0) free(buffer0);
        if (buffer1) free(buffer1); //this is probably pedantic, but we'll leave it in anyway
      }
      else break; // everything went well!
    }
  }
}
