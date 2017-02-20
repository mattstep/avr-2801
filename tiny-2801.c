#include <avr/io.h>
#include <util/delay.h>

const unsigned char CLOCK_PIN = 4;
const unsigned char DATA_PIN = 3;

void writeByte(unsigned char data) {
	DDRB = (1 << CLOCK_PIN) | (1 << DATA_PIN);
	unsigned char clock_value = (0x01 << CLOCK_PIN);
	unsigned char datum;
	unsigned char i;
	for(i=0; i<8; i++) {
		datum = ((data >> 7) << DATA_PIN);
		PORTB = 0x00 | datum;
		_delay_us(10);
		PORTB = clock_value | datum;
		data <<= 1;
	}
}

void writeColorData(unsigned char red, unsigned char green, unsigned char blue) {
	writeByte(red);
	writeByte(green);
	writeByte(blue);
}

void latchData() {
	PORTB = 0x00;
	_delay_ms(100);
}