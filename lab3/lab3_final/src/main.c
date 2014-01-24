#include "main.h"

extern unsigned char xdata heap[HEAP_SIZE];

void setup(void);
void get_buffers(void);
void prompt(void);
void hexdump(char const * buffer, int len);

#define MAX_INPUT_LEN 128
#define N_STAT_LETTERS    14

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
  char stat_letters[N_STAT_LETTERS] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'F', 'E', 'M', 'A'};

  // initialize heap
  setup();

  // prompt user for size, allocate buffers.
  // Blocks while waiting for correct input
  get_buffers();

  prompt();

  // store the number of occurrences of each ascii character
  for (i = 0; i < 256; i++) {
    numberof[i] = 0;
  }

  while(1) {
    // print a prompt every 50 characters
    if (n_chars % 50 == 0) printf("\n>> ");

    // get a character (getchar() echoes)
    c = getchar();

    if (c == 0x08) {
      n_chars--;
      numberof[buffer0[n_chars]]--;
      continue;
    }

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

    // flush
    if (c == '?') {
      // print general stats
      printf("\nStored ");
      printn(n_stored, 10, 0);
      printf(" characters in buffer0, with ");
      printn(buff_len - n_stored, 10, 0);
      printf(" free\n");

      printf("Buffer 0: ");
      printn(buff_len, 10, 0);
      printf(" bytes at ");
      printn((int) buffer0, 16, 4);
      putchar('\n');

      printf("Buffer 1: ");
      printn(buff_len/4, 10, 0);
      printf(" bytes at ");
      printn((int) buffer1, 16, 4);
      putchar('\n');

      // print stats for stat_letters letter 
      for (i = 0; i < N_STAT_LETTERS; i++) {
        if (i % 10 == 0) printf("\n");
        putchar(stat_letters[i]);
        putchar('-');
        printn(numberof[stat_letters[i]],10, 0);
        putchar(' ');

        numberof[stat_letters[i]] = 0;
      }

      // clear buffer, printing to screen
      printf("\n\nFlushing buffer...");
      for (i = 0; i < n_stored; i++) {
        if (i % 50 == 0) putchar('\n');
        putchar(buffer0[i]);
      }
      printf("\n\n");

      // actually clear buffer
      n_stored = 0;
      n_chars = 0;

      prompt();
    }

    // report
    if (c == '=') {
      putchar('\n');
      hexdump(buffer0, n_stored);
      putchar('\n');

      printf("\n>> ");
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
    printf("Enter your buffer size (in the range [24 1600] and a multiple of 8): ");
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
  printf("\n    + 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F");

  for (i = 0; i < len; i++) {
    if (i % 16 == 0) {
      printf("\n");
      printn((int) (buffer + i), 16, 4);
      printf(": ");
    }
    printn(buffer[i], 16, 2);
    putchar(' ');
  }
  printf("\n");
}

void prompt(void)
{
  // print instructions
  printf("\nEnter characters for storage.\n");
  printf("\t=\thex dump of buffer contents\n");
  printf("\t?\tprint stats and clear buffer\n");
}
