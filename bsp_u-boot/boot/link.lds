
SECTIONS
{
	. = 0x80008000;
	.text : {
	 	_stext = .;
	 	*(.text)
	 }
	.rodata : {
		*(.rodata)
		*(.rodata.*)
		_etext = .;
	}
	.data ALIGN(4096) : {
		_sdata = .;
		*(.data)
	}
        . = ALIGN(4);
 	. = .;
 	__u_boot_cmd_start = .;
 	.u_boot_cmd : { *(.u_boot_cmd) }
 	__u_boot_cmd_end = .;
        
        . = ALIGN(4);

        __image_copy_end = .;

        .rel.dyn : {
                __rel_dyn_start = .;
                *(.rel*)
                __rel_dyn_end = .;
        }

        .dynsym : {
                __dynsym_start = .;
                *(.dynsym)
        }


        _end = .;
	.bss : {
	       __bss_start__ = .;
		*(.bss)
		_edata = ALIGN(4096);
		__bss_end__ = _edata;
	}
/*	/DISCARD/ : {
	*(.comment)
	}*/
}

