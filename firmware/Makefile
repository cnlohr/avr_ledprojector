
all : test.hex burn
PART=attiny44
PROGPART=t44

CFLAGS=-g -Os -mmcu=$(PART) -DF_CPU=8000000UL -flto -fwhole-program -DMUTE_PRINTF
CC=avr-gcc
AS = avr-gcc
ASFLAGS = $(COMMON_FLAGS) -c
EXTRA_LD_FLAGS=


test.elf : test.c avr_print.c mcp23008.c mlx90614.c
	avr-gcc -I. $(CFLAGS) -Wl,--relax -mcall-prologues  -Wl,-Map,test.map -o $@ $^ -L/usr/lib/binutils/avr/2.18

test.hex : test.elf
	avr-objcopy -j .text -j .data -O ihex test.elf test.hex 

burn : test.hex
	avrdude -c usbtiny -p $(PROGPART) -U flash:w:test.hex
# if you get the part borked, type -B 1024 and it will go REALLY slow

#This make the part use an external crystal.
burnfuses :
	avrdude -c usbtiny -p $(PROGPART) -U lfuse:w:0xde:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m 

readfuses :
	avrdude -c usbtiny -p $(PROGPART) -U hfuse:r:high.txt:b -U lfuse:r:low.txt:b

clean : 
	rm -f *~ high.txt low.txt test.hex test.map test.elf *.o
