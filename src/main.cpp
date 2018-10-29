#include "VgaBuffer.h"
#include "multiboot.h"
#include "GlobalDescriptorTable.h"
#include "InterruptsManager.h"
#include "KbdHandler.h"
#include "Shell.h"
#include "DisplayablesManager.h"

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
	VgaBuffer::enableCursor(0, 15);

	GlobalDescriptorTable gdt;
	InterruptsManager interruptsManager(&gdt);

	DisplayablesManager displayablesManager;

	// Shell commands
	String reboot("reboot");

	Shell basicShell;
	basicShell.addCommand(&reboot);

	displayablesManager.addDisplayable(&basicShell);
	KbdHandler kbd(&interruptsManager, &displayablesManager);

	interruptsManager.initIdt();

	basicShell.start();

	return;
}
