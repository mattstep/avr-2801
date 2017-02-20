TARGET=lightGlobe
BIN=/usr/local/bin

.PHONY: build program default clean

default: build

clean:
	rm -f $(TARGET).out $(TARGET).hex

build: 
	$(BIN)/avr-gcc -g -Os -mmcu=attiny85 -o $(TARGET).out -c $(TARGET).c
	$(BIN)/avr-gcc -g -mmcu=attiny85 -o $(TARGET).elf $(TARGET).out
	$(BIN)/avr-objcopy -O ihex -j .text -j .data -R .eeprom $(TARGET).elf $(TARGET).hex

program: build
	sudo avrdude -c avrispmkii -P usb -B 10 -v -e -p t85 -Ulfuse:w:0xE2:m
	sudo avrdude -c avrispmkii -P usb -B 10 -v -e -p t85 -Uflash:w:$(TARGET).hex
