#include <at89c51ed2.h>

int main(void) {
  int i;

  while(1) {
    P1_1 ^= 0x01;    

    for (i = 0; i < 10000; i++);
  }
}
