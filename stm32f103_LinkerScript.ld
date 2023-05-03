/* 
	@file	LinkerScript.ld
	@autoh	Ahmed Tarek
	@brief	Linker script for STM32F103c8 Device from STM32F1 seris
*/	

_estack = ORIGIN(SRAM) + LENGTH(SRAM) ;

_Min_Heap_Size = 0x200 ; /* 0.5KB for the heap */
_Min_Stack_Size = 0x400 ; /* 1KB for the stack */

ENTRY(Reset_Handler)

MEMORY
{
	FLASH(rx) : ORIGIN = 0x08000000 , LENGTH = 64K
	SRAM(rwx) : ORIGIN = 0x20000000 , LENGTH = 20K
}

SECTIONS
{
	.isr_vectors :
	{
		*(.isr_vectors)	
		
	} >FLASH
	
	.text :
	{
		. = ALIGN(4);
		_stext = . ;
		*(.text)
		*(.text*)
		_etext = . ;
		. = ALIGN(4);
		
	} >FLASH
	
	.rodata :
	{
		. = ALIGN(4);
		_srodata = . ;
		*(.rodata)
		*(.rodata*)
		_erodata = . ;
		. = ALIGN(4);
		
	} >FLASH
	
	.data :
	{
		. = ALIGN(4);
		_sdata = . ;
		*(.data)
		*(.data*)
		_edata = . ;
		. = ALIGN(4);
		
	} >SRAM AT> FLASH
	
	.bss :
	{
		. = ALIGN(4);
		_sbss = . ;
		*(.bss)
		*(.bss*)
		_ebss = . ;
		. = ALIGN(4);
				
	} >SRAM
	
	.user_heap_stack :
	{
		. = ALIGN(8);
		. = . + _Min_Heap_Size;
		. = . + _Min_Stack_Size;
		. = ALIGN(8);	
	} >SRAM
}