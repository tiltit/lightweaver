PRG 			= lightweaver

MCU_TARGET		= atmega328p
SYSTEM_CLOCK	= 16000000UL

DEFS			=
LIBS			=

CC 				= avr-gcc
CSTANDARD 		= gnu99 

OBJCOPY			= avr-objcopy
OBJDUMP			= avr-objdump

ODIR			= obj
SOURCES			= main.c cb.c motor_control.c lib/xprintf.c serial.c
OBJECTS			= $(addprefix $(ODIR)/, $(SOURCES:.c=.o))
DEPS 			= cb.h motor_control.h serial.h lib/xprintf.h serial_commands.h

all: $(PRG).hex

$(PRG).hex: $(PRG).elf
	$(OBJCOPY) -O ihex -R .eeprom $(PRG).elf $(PRG).hex

$(PRG).elf: $(OBJECTS)
	$(CC) -mmcu=$(MCU_TARGET) $(OBJECTS) -o $(PRG).elf

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -Os --std=$(CSTANDARD) -DF_CPU=$(SYSTEM_CLOCK) -mmcu=$(MCU_TARGET) -c -o $@ $< $(LIBS)

$(PRG).lst: $(PRG).elf
	$(OBJDUMP) -h -S $(PRG).elf > $(PRG).lst

$(PRG).map: $(PRG).elf $(OBJECTS)
	$(CC) -g -mmcu=$(MCU_TARGET) -Wl,-Map,$(PRG).map -o $(PRG).elf $(OBJECTS)


flash: $(PRG).hex
	avrdude -F -V -c arduino  -p atmega328p -P /dev/ttyUSB0 -b 115200 -U flash:w:$(PRG).hex
	#avrdude -F -V -c stk500v2  -p ATMEGA328P -P /dev/stk500-programmer0 -b 115200 -U flash:w:$(PRG).hex

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o *.elf *.lst *.map

