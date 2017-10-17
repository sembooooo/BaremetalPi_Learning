ARMGNU = arm-none-eabi

CFLAGS = -Wall  -O2 -nostartfiles -nostdlib -march=armv8-a -mtune=cortex-a53 -g -c

INC = -I ./

all : kernel.img

startup.o : startup.s
	$(ARMGNU)-as startup.s -o startup.o

main.o : main.c
	$(ARMGNU)-gcc $(CFLAGS) $(INC) main.c -o main.o


output.elf: main.o startup.o
	$(ARMGNU)-ld  startup.o main.o -T linker.ld -Map=output.map -o  output.elf

kernel.img: output.elf
	$(ARMGNU)-objcopy output.elf -O binary kernel.img
	$(ARMGNU)-objdump -D output.elf > output.list
	$(ARMGNU)-nm -n output.elf > output.symbol
	rm -f *.o

clean:
	rm -f *.o *.elf *.img *.map *.list *.symbol

