ENTRY(Reset_Handler)

MEMORY
{
	FLASH(rx) : ORIGIN = 0x08000000 , LENGTH = 64K
	SRAM(rwx) : ORIGIN = 0x20000000 , LENGTH = 20K
}

SECTIONS
{
	.text :
	{
		*(.isr_vectors)
		*(.text)
		*(.rodata)
		_etext = . ;
		
	} >FLASH
	
	.data :
	{
		_sdata = . ;
		*(.data)
		_edata = . ;
		
	} >SRAM AT> FLASH
	
	.bss :
	{
		_sbss = . ;
		*(.bss)
		_ebss = . ;
				
	} >SRAM
}