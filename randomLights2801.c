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
	_delay_ms(10);
}

const unsigned char NUMBER_OF_LIGHTS = 25;

void singleTrace(unsigned char brightness, char direction) {
	unsigned char lightOn;
	unsigned char i;
	unsigned char j;
	for(j = 0; j < NUMBER_OF_LIGHTS; j++) {
		for( i=0; i<NUMBER_OF_LIGHTS; i++) {
			lightOn = (direction*j) % NUMBER_OF_LIGHTS;
			writeColorData(brightness*(i == lightOn), 0, 0);
		}
		latchData();
	}
	for(j = 0; j < NUMBER_OF_LIGHTS; j++) {
		for( i=0; i<NUMBER_OF_LIGHTS; i++) {
			writeColorData(brightness*(i == lightOn), brightness*(i == lightOn), 0);
		}
		latchData();
	}
	for(j = 0; j < NUMBER_OF_LIGHTS; j++) {
		for(i=0; i<NUMBER_OF_LIGHTS; i++) {
			writeColorData(0, brightness*(i == lightOn), 0);
		}
		latchData();
	}
	for(j = 0; j < NUMBER_OF_LIGHTS; j++) {
		for(i=0; i<NUMBER_OF_LIGHTS; i++) {
			writeColorData(0, brightness*(i == lightOn), brightness*(i == lightOn));
		}
		latchData();
	}
	for(j = 0; j < NUMBER_OF_LIGHTS; j++) {
		for(i=0; i<NUMBER_OF_LIGHTS; i++) {
			writeColorData(0, 0, brightness*(i == lightOn));
		}
		latchData();
	}	
	for(j = 0; j < NUMBER_OF_LIGHTS; j++) {
		for(i=0; i<NUMBER_OF_LIGHTS; i++) {
			writeColorData(brightness*(i == lightOn), 0, brightness*(i == lightOn));
		}
		latchData();
	}
	for(j = 0; j < NUMBER_OF_LIGHTS; j++) {
		for(i=0; i<NUMBER_OF_LIGHTS; i++) {
			writeColorData(brightness*(i == lightOn), brightness*(i == lightOn), brightness*(i == lightOn));
		}
		latchData();
	}
	for(j = 0; j < NUMBER_OF_LIGHTS; j++) {
		for(i=0; i<NUMBER_OF_LIGHTS; i++) {
			writeColorData(brightness*(i == lightOn), 0, brightness*(i == lightOn));
		}
		latchData();
	}
	for(j = 0; j < NUMBER_OF_LIGHTS; j++) {
		for(i=0; i<NUMBER_OF_LIGHTS; i++) {
			writeColorData(0, 0, brightness*(i == lightOn));
		}
		latchData();
	}
	for(j = 0; j < NUMBER_OF_LIGHTS; j++) {
		for(i=0; i<NUMBER_OF_LIGHTS; i++) {
			writeColorData(0, brightness*(i == lightOn), brightness*(i == lightOn));
		}
		latchData();
	}	
	for(j = 0; j < NUMBER_OF_LIGHTS; j++) {
		for(i=0; i<NUMBER_OF_LIGHTS; i++) {
			writeColorData(0, brightness*(i == lightOn), 0);
		}
		latchData();
	}
	for(j = 0; j < NUMBER_OF_LIGHTS; j++) {
		for( i=0; i<NUMBER_OF_LIGHTS; i++) {
			writeColorData(brightness*(i == lightOn), brightness*(i == lightOn), 0);
		}
		latchData();
	}
}

unsigned char dec(unsigned char n, unsigned char m) {
	if(n < m) {
		return 0x00;
	}
	return n - m;
}

unsigned char inc(unsigned char n, unsigned char m) {
	if((0xff - n) < m) {
		return 0xff;
	}
	return n + m;
}

void gradient() {
	unsigned char segment = NUMBER_OF_LIGHTS/3;
	unsigned char red = 0xff;
	unsigned char blue = 0x00;
	unsigned char green = 0x00;
	
	unsigned char i;
	unsigned char j;
    for(j = 0; j < NUMBER_OF_LIGHTS; j++) {
		for(i = 0; i < 2*NUMBER_OF_LIGHTS; i++) {
			if(i >= j)
				writeColorData(red, green, blue);
			
			unsigned char k = i % NUMBER_OF_LIGHTS;
			
			if(k <=  segment) {
		 		green = inc(green, 0x20);
		 		red   = dec(red, 0x20);
			} else if(k <= (segment << 1)) {
		 		blue  = inc(blue, 0x20);
		 		green = dec(green, 0x20);
			} else {
		 		red  = inc(red, 0x20);
		 		blue = dec(blue, 0x20);
			}
		}
		latchData();
	}
}

int main(void) {
	while(1) {
		singleTrace(0xff, 1);
		
		unsigned char i;
		for(i = 0; i < 10; i++) {
			gradient();
		}

		singleTrace(0xff, -1);
	}
}