#include "getstring.h"

char * getstring(char * buff, int buff_len)
{
  int i;
  char c;

  if (buff_len <= 0) return NULL;

  for (i = 0; i < (buff_len - 1); i++) {
    c = getchar();

    if (c == '\n' || c == '\r') {
      putchar('\n');
      break;
    }

    buff[i] = c;
  }
  buff[i] = '\0';

  return buff;
}
