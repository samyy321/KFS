#include "VgaBuffer.h"
#include "multiboot.h"
#include "GlobalDescriptorTable.h"
#include "InterruptsManager.h"
#include "KbdHandler.h"

void	printSplash(void)
{
	int i;
	int j;

	VgaBuffer::putstr("De l'or tu dis ?\n");
	for (i = 0; i < HEIGHT - 1; ++i)
	{
		for (j = 0; j < 1000000; ++j){}
		VgaBuffer::putstr(".\n");
	}
	VgaBuffer::putstrColor("Flemme sur lit de pistache.", LIGHT_GREEN, RED);
}

extern "C"
void	kmain(t_multiboot *mboot_ptr)
{
	VgaBuffer::clear();
	printSplash();

	GlobalDescriptorTable gdt;
	InterruptsManager interruptsManager(&gdt);
	return;
}
