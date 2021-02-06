ENTRY(Reset_Handler)

/* Memory configuration for STM32L011 */

MEMORY
{
	flash	:	ORIGIN = 0x08000000, LENGTH = 16K
	sram	:	ORIGIN = 0x20000000, LENGTH = 2K
}

_end_stack = 0x20000800;

SECTIONS {
	. = ORIGIN(flash);

	vectors :
	{
		*(.vectors)
	} >flash

	. = ALIGN(4);

	.text :
	{
		*(.text*)
		*(.rodata*)
	} >flash

	. = ALIGN(4);

	.data :
	{
		_start_data = .;
		*(.data*)
		_end_data = .;
	} >sram AT >flash

    _start_data_flash = LOADADDR(.data);

	. = ALIGN(4);

	.bss :
	{
		_start_bss = .;
		*(.bss*)
		_end_bss = .;
	} >sram

	. = ALIGN(4);

	_start_stack = .;
}

_end = .;
PROVIDE(end = .);

