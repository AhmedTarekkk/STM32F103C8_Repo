CC = arm-none-eabi-gcc

#Analyze object file to see the assembly
ASM = arm-none-eabi-objdump -d

#Analyze object file to see the assembly
Analyze = arm-none-eabi-objdump -h

MACH = cortex-m3

CFLAGS = -c -mcpu=$(MACH) -mthumb

LDFLAGS = -nostdlib -T stm32f103_LinkerScript.ld -Wl,-Map=final.map

main.o:main.c
	$(CC) $(CFLAGS) $^ -o $@
	
GPIO_program.o:GPIO_program.c
	$(CC) $(CFLAGS) $^ -o $@
	
RCC_program.o:RCC_program.c
	$(CC) $(CFLAGS) $^ -o $@
	
STK_program.o:STK_program.c
	$(CC) $(CFLAGS) $^ -o $@
	
stm32f103_startup.o:stm32f103_startup.c
	$(CC) $(CFLAGS) $^ -o $@

main.s:main.c
	$(CC) -mcpu=$(MACH) -S $< -o $@

##########################################
all_o : *.c
	$(CC) $(CFLAGS) $^
##########################################


main_log.s:main.o
	$(ASM) $< > $@
	
GPIO_log.s:GPIO_program.o
	$(ASM) $< > $@
	
stm32f103_startup.s:stm32f103_startup.o
	$(ASM) $< > $@

all_s : *.o
	$(ASM) $^ > $@

stm32f103_analyze.s:stm32f103_startup.o
	$(Analyze) $< > $@

analyze.s:*.o
	$(Analyze) $^ > $@
		

symbol.txt:final.elf
	arm-none-eabi-nm $^ > $@

clean:
	rm -rf *.o *.elf *.s *.map *.txt

final.elf : all_o
	$(CC) $(LDFLAGS) main.o GPIO_program.o RCC_program.o STK_program.o stm32f103_startup.o -o $@
	
allv2:main.o GPIO_program.o RCC_program.o STK_program.o stm32f103_startup.o final.elf

all:all_o final.elf analyze.s

gdb:
	arm-none-eabi-gdb

localhost:
	target remote localhost:3333

#Ctrl+c to close connection
Load:
	openocd -f interface/stlink-v2.cfg -f board/stm32f103c8_blue_pill.cfg