#include "VgaBuffer.h"
#include "multiboot.h"
#include "GlobalDescriptorTable.h"
#include "InterruptsManager.h"
#include "KbdHandler.h"
#include "Shell.h"
#include "DisplayablesManager.h"
#include "CommandsManager.h"
#include "RebootCmd.h"
#include "GodGiveCmd.h"
#include "GodTakeCmd.h"

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

//Need this handler because of lack of std lib
extern "C" void __cxa_pure_virtual()
{
	while(1);
}

extern "C"
void	kmain(t_multiboot *mboot_ptr)
{
	VgaBuffer::clear();
	printSplash();
	VgaBuffer::enableCursor(0, 15);

	GlobalDescriptorTable gdt;

	// Shell commands
	RebootCmd rebootCmd;
	GodGiveCmd godGiveCmd;
	GodTakeCmd godTakeCmd;

	CommandsManager cmdManager;
	cmdManager.addCommand(&rebootCmd);
	cmdManager.addCommand(&godGiveCmd);
	cmdManager.addCommand(&godTakeCmd);

	Shell basicShell(&cmdManager);

	DisplayablesManager displayablesManager;
	displayablesManager.addDisplayable(&basicShell);

	InterruptsManager interruptsManager(&gdt);
	KbdHandler kbd(&interruptsManager, &displayablesManager);
	interruptsManager.initIdt();

	basicShell.start();

	return;
}
