#include "main.h"

#define BUFF_LEN 128

char xdata buffer[BUFF_LEN];

int main(void)
{
  int n;
  char * endptr;
  char * mal_buff = NULL;
  malloc_setup();

  while (!mal_buff) {
    printf("Enter a buffer size: ");
    getstring(buffer, BUFF_LEN);

    n = strtoi(buffer, &endptr);
    if (*buffer != '\0' && *endptr == '\0' && n > 0) mal_buff = (char *) malloc(n);
  }

  printf("You got a buffer of size "); printn(n, 10, 0);
  printf(" at location "); printn((int) mal_buff, 16, 4);
  putchar('\n');
  
  while(1) putchar(getchar());
}
