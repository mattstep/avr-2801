#include <avr/io.h>
#define F_CPU 8000000UL  // 8 MHz
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
		_delay_us(1);
		PORTB = 0x00 | datum;
		_delay_us(1);
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
	_delay_us(500);
}

unsigned char intensity = 0x80;

void lateralTraces(unsigned char count) {
	unsigned char n = 0;
	unsigned char i = 0;
	unsigned char j = 0;
	
	unsigned char offset = 12;
	
	if (count > 1) {
		offset = 12 / count;
	}
	
	for(n = 0; n < 16 * offset; n++) {
		for(i = 0; i < 12; i++) {
			for(j = 0; j < 16; j++) {
				
				unsigned char position = i % 2 ? i * 12 + j : i * 12 + 15 - j;
			
				unsigned char vertical = (n >> 4);
				
				unsigned char coeff = 0;
				bool shouldUpdate = false;
				for(coeff = 0; coeff < count; coeff++) {
					shouldUpdate |= (vertical + offset * coeff == i);
				}
				
				if (!shouldUpdate) {
					writeColorData(0, 0, 0);
				} else {
					unsigned char red = 0;
					unsigned char green = 0;
					unsigned char blue = 0;

					if (n == position) {
						red = intensity;
						green = intensity;
						blue = intensity;
					} else if (n == position - 1 && j > 1) {
						red = 0.8*intensity;
						blue = 0.8*intensity;
					} else if (n == position - 2 && j > 2) {
						blue = 0.7*intensity;
					} else if (n == position - 3 && j > 3) {
						blue = 0.4*intensity;
						green = 0.6*intensity;
					} else if (n == position - 4 && j > 4) {
						green = 0.7*intensity;
					} else if (n == position - 5 && j > 5) {
						red = 0.3*intensity;
						green = 0.4*intensity;
					} else if (n == position - 6 && j > 6) {
						red = 0.3*intensity;
						green = 0.2*intensity;
					} else if (n == position - 7 && j > 7) {
						red = 0.3*intensity;
					}
					writeColorData(red, green, blue);
				}
			}
		}
		latchData();
	}
}

int main() {
	while(1) {
		singleLateralTraces(1);
		singleLateralTraces(2);
		singleLateralTraces(3);
		singleLateralTraces(3);
	}
}