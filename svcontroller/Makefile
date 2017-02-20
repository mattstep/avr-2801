TARGET=svc
BIN=/usr/local/bin
.PHONY: build program default clean

default: build

clean:
	rm -f $(TARGET).out $(TARGET).hex

build: 
	$(BIN)/avr-gcc -Ii2cmaster/ -g -Os -mmcu=attiny13a -o $(TARGET).out -c $(TARGET).c
	$(BIN)/avr-gcc -B/usr/local/Cellar/avr-gcc/4.7.0/avr/lib/avr25/ -g -mmcu=attiny85 -o $(TARGET).elf $(TARGET).out i2cmaster/i2cmaster.o
	$(BIN)/avr-objcopy -O ihex -j .text -j .data -R .eeprom $(TARGET).elf $(TARGET).hex

program: build
#	sudo avrdude -c avrispmkii -P usb -B 10 -v -e -p t85 -Uhfuse:w:0xDF:m -Ulfuse:w:0x62:m
	sudo avrdude -c avrispmkii -P usb -B 10 -v -e -p t85 -Uflash:w:$(TARGET).hex
