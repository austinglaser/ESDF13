#include "main.h"

extern unsigned char xdata heap[HEAP_SIZE];

// run all setup functions. Currently just initializes heap
void setup(void);

// get the user's desired buffer size, attempt allocation
void get_buffers(void);

// print a prompt with instructions
void prompt(void);

// dump buffer as hex, with 'len' specifying
// how many elements in the buffer are
// valid.
void hexdump(char const * buffer, int len);

// Print statistics about current buffer contents,
// print ascii contenst to the screen, and empty
// the buffer
void flush();

#define MAX_INPUT_LEN   128
#define N_STAT_LETTERS  14

// global vars
long near buff_len;
int xdata numberof[256];
volatile char stat_letters[N_STAT_LETTERS + 1];
volatile int near n_stored = 0;
volatile int near n_chars = 0;
volatile int near n_atprompt = 0;

//pointers to heap-allcoated memory
char xdata * buffer0;
char xdata * buffer1;

int main(void)
{
  int i;
  char c;

  DEBUGPORT('e');

  // initialize heap
  setup();

  DEBUGPORT('i');

  // prompt user for size, allocate buffers.
  // Blocks while waiting for correct input
  get_buffers();
  
  DEBUGPORT('a');

  n_stored = 0;
  n_chars = 0;
  n_atprompt = 0;
  memcpy(stat_letters, "0123456789FEMA", N_STAT_LETTERS + 1);

  // print variable initial values, for debut purposes
#ifdef DEBUG
  printf("Initial Info:\n");
  printf("&n_stored: "); printn((unsigned) &n_stored, 16, 0);   putchar('\n');
  printf("&n_chars: "); printn((unsigned) &n_chars, 16, 0);   putchar('\n');
  printf("&n_atprompt: "); printn((unsigned) &n_atprompt, 16, 0);   putchar('\n');
  printf("&buffer0: "); printn((unsigned) buffer0, 16, 0);   putchar('\n');
  printf("&buffer1: "); printn((unsigned) buffer1, 16, 0);   putchar('\n');
  printf("&numberof: "); printn((unsigned) numberof, 16, 0);   putchar('\n');
  putchar('\n');
#endif

  prompt();

  // store the number of occurrences of each ascii character
  for (i = 0; i < 256; i++) {
    numberof[i] = 0;
  }

  while(1) {
    // print a prompt every 50 characters
    if (n_atprompt == 50) {
      printf("\n>> ");
      n_atprompt = 0;
    }

    // get a character
    c = getchar();

    // backspace handler
    if (c == 0x08) {
      // if there's something in the buffer,
      // we remove the last character
      if (n_stored > 0) {
        n_stored--;
        numberof[buffer0[n_stored]]--;
      }

      // if there are characters at the prompt,
      // delete them. This is purely UI sugar --
      // it would be nice to be able to go back a line but
      // that is not nearly as straightforward.
      if (n_atprompt > 0) {
        putchar(0x08);
        putchar(' ');
        putchar(0x08);
        n_atprompt--;
      }

      // skip the rest of the loop
      continue;
    }
    // if it's not a backspace character, just echo
    else putchar(c);

    // log the character
    n_chars++;
    n_atprompt++;
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
      flush();

      // prompt the user
      prompt();
    }

    // report
    if (c == '=') {
      // hex dump buffer
      hexdump(buffer0, n_stored);

      // give user a prompt
      printf("\n>> ");
      n_atprompt = 0;
    }
  }
}

void setup(void)
{
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

  DEBUGPORT('h');

  // top border
  printf("\n\n+");
  for (i = 0; i < 55; i++) putchar('-');
  putchar('+');

  // left border
  printf("\n| ");

  // header line
  printf("      +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F");

  for (i = 0; i < len; i++) {
    // every 16 bytes, print a border and
    // address info
    if (i % 16 == 0) {
      // border
      finish_line('|', 57); printf("\n| ");
      
      // address info
      printn((int) (buffer + i), 16, 4); printf(": ");
    }

    // buffer value
    printn(buffer[i], 16, 2);
    putchar(' ');
  }

  // right border
  finish_line('|', 57);
  
  // bottom border
  printf("\n+");
  for (i = 0; i < 55; i++) putchar('-');
  printf("+\n");

  DEBUGPORT('d');
}

void prompt(void)
{
  // print instructions
  printf("\nEnter characters for storage.\n");
  printf("\t=\thex dump of buffer contents\n");
  printf("\t?\tprint stats and clear buffer\n");

  printf("\n>> ");

  n_atprompt = 0;
}

void flush(void) {
  int i;

  DEBUGPORT('f');

  // print top of box. before every newline, we finish the line with the right side.
  // It might make sense to do this automatically with putchar (toggle box on/off
  // with a global variable) but for now, it's all manual.
  printf("\n\n+");
  for (i = 0; i < 55; i++) putchar('-');
  printf("+\n| ");
  
  // give statistics about buffer state
  printf("Recieved "); printn(n_chars, 10, 0);
  printf(" characters since last flush.");

  // box borders
  finish_line('|', 57); printf("\n| ");
  finish_line('|', 57); printf("\n| ");

  // give statistics about buffer state
  printf("Stored "); printn(n_stored, 10, 0);
  printf(" characters in buffer0, with "); printn(buff_len - n_stored, 10, 0); printf(" free");

  // box borders
  finish_line('|', 57); printf("\n| ");

  // buffer 0 size
  printf("Buffer 0: "); printn(buff_len, 10, 0);
  printf(" bytes at "); printn((int) buffer0, 16, 4);

  // box borders
  finish_line('|', 57); printf("\n| ");

  // buffer 1 size
  printf("Buffer 1: "); printn(buff_len/4, 10, 0);
  printf(" bytes at "); printn((int) buffer1, 16, 4);

  // box borders
  finish_line('|', 57); printf("\n| ");

  // print stats for important letters
  for (i = 0; i < N_STAT_LETTERS; i++) {
    // box borders every 12 letters (12 letters = 47 chars.
    // We can fit 50 in the box, so that's the max
    if (i % 8 == 0){
      finish_line('|', 57); printf("\n| ");
    }
    
    // stats about the letter are stored in the lookup
    // table 'numberof[]'. the particular letters
    // we want are stored inthe stat_letters[] array.
    // This makes it very easy to change which letters
    // we print information about (info is *recorded*
    // about all letters). By making the array
    // dynamically allocated, we could easily make this an interactive
    // feature of the program
    putchar(stat_letters[i]); putchar('-');
    printn(numberof[stat_letters[i]],10, 0); putchar(' ');

    // zero out the lut
    numberof[stat_letters[i]] = 0;
  }
  
  // box borders 
  finish_line('|', 57); printf("\n| ");
  finish_line('|', 57); printf("\n| ");

  // print and clear buffer
  printf("Flushing buffer...");
  for (i = 0; i < n_stored; i++) {
    // print a border every 50 characters
    if (i % 50 == 0) {
      finish_line('|', 57); printf("\n| ");
    }
    putchar(buffer0[i]);
  }
  finish_line('|', 57);

  // print the bottom border
  printf("\n+");
  for (i = 0; i < 55; i++) putchar('-');
  printf("+\n");

  // actually clear buffer. We don't
  // write zeroes in, just record that
  // it's empty
  n_stored = 0;
  n_chars = 0;
  n_atprompt = 0;

  DEBUGPORT('d');
}
