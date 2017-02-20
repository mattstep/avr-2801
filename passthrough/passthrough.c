#include <avr/io.h>

int main(void) {
  while(1) {
    DDRB = 0x03;
    PORTB = PINB >> 3;
  }
}
