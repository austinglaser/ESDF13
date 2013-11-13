#include <serial.h>

int main(void) {
  serial_init();
  while (1) {
    serial_putc('U');
  }
}
