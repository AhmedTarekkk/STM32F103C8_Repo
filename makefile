CC = arm-none-eabi-gcc

#Analyze object file to see the assembly
ASM = arm-none-eabi-objdump -d

#Analyze object file to see its content
Analyze = arm-none-eabi-objdump -h

#Analyze object file to see its symbol table
#To print the symbol table use
#arm-none-eabi-objdump -t file.o
SymbolTable = arm-none-eabi-objdump -t

MACH = cortex-m3

CFLAGS = -c -mcpu=$(MACH) -mthumb --debug

LDFLAGS = -nostdlib -T stm32f103_LinkerScript.ld -Wl,-Map=final.map

CONV = arm-none-eabi-objcopy -O
HEX = ihex
BIN = binary

##########################################

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

final.lss : all_o
	$(ASM) *.o > $@

##########################################

stm32f103_analyze.s:stm32f103_startup.o
	$(Analyze) $< > $@

analyze.s: all_o
	$(Analyze) *.o > $@

mainSymbolTable.s:main.o
	$(SymbolTable) $<
##########################################

symbol.txt:final.elf
	arm-none-eabi-nm $^ > $@
##########################################

all: final.hex analyze.s final.lss symbol.txt

allv2:main.o GPIO_program.o RCC_program.o STK_program.o stm32f103_startup.o final.elf 

clean:
	rm -rf *.o *.elf *.s *.asm *.map *.txt *.lss *.bin *.hex *.i

final.elf : all_o
	$(CC) $(LDFLAGS) *.o -o $@

final.hex : final.elf
	$(CONV) $(HEX) $^ $@
	
final.bin : final.elf
	$(CONV) $(BIN) $^ $@

##########################################

gdb:
	arm-none-eabi-gdb

localhost:
	target remote localhost:3333

#Ctrl+c to close connection
Load:
	openocd -f interface/stlink-v2.cfg -f board/stm32f103c8_blue_pill.cfg