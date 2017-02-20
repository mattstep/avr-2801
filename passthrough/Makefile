TARGET=passthrough
BIN=/usr/local/bin/
.PHONY: build program default clean

default: build

clean:
	rm -f $(TARGET).out $(TARGET).hex

build: 
	$(BIN)/avr-gcc  -g -Os -mmcu=attiny13a -o $(TARGET).out -c $(TARGET).c
	$(BIN)/avr-gcc -B/usr/local/Cellar/avr-gcc/4.7.0/avr/lib/avr25/ -g -mmcu=attiny13a -o $(TARGET).elf $(TARGET).out
	$(BIN)/avr-objcopy -O ihex -j .text -j .data -R .eeprom $(TARGET).elf $(TARGET).hex

program: build
	sudo avrdude -c avrispmkii -P usb -B 10 -v -e -p t13 -Uhfuse:w:0xFF:m -Ulfuse:w:0x7A:m
	sudo avrdude -c avrispmkii -P usb -B 10 -v -e -p t13 -Uflash:w:$(TARGET).hex
