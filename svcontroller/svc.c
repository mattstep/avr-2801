#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <i2cmaster.h>

#define TC74Address 0x90
#define TC74ReadTemp 0x00

#define OnTemp 60
#define RelayPin 4 
#define SwitchingDelay 100

char currentTemp = 0;
char isHeating = 0;

unsigned char getTemp() {
  i2c_init();
  i2c_start_wait(TC74Address + I2C_WRITE);
  i2c_write(0x00);
  i2c_rep_start(TC74Address + I2C_READ);
  char temp = i2c_readNak();
  i2c_stop();
  return temp;
}

void enableHeater() {
  PORTB = PINB | (1 << RelayPin);
  isHeating = 1;
}

void disableHeater() {
  PORTB = PINB & ~(1 << RelayPin);
  isHeating = 0;
}

int main(void) {
  DDRB = (1 << RelayPin);  
  while(1) {
    
    currentTemp = getTemp();
    
    if(currentTemp < OnTemp && !isHeating) {
      _delay_ms(SwitchingDelay);
      currentTemp = getTemp();
      if(currentTemp < OnTemp) {
        enableHeater();
      }
    }

    if(currentTemp > OnTemp && isHeating) {
      _delay_ms(SwitchingDelay);
      currentTemp = getTemp();
      if(currentTemp > OnTemp) {
        disableHeater();
      }
    }

    //_delay_ms(100);
  }
}
