#include "GodGiveCmd.h"
#include "lib.h"
#include "types.h"

GodGiveCmd::GodGiveCmd(): Command("godgive")
{

}

void GodGiveCmd::writeToMemory(String& str, uint32_t addr)
{
	MemLib::memcpy((void*)addr, (char*)str, str.getSize());
}

void GodGiveCmd::exec()
{
	String userInput(Command::getArg(0));
	uint32_t addr = (uint32_t)Utils::atoi(getArg(1));
	writeToMemory(userInput, addr);

	VgaBuffer::putstr("String: ");
	VgaBuffer::putstrColor((char*)userInput, BLACK, LIGHT_GREEN);
	VgaBuffer::putstr(" written at adress: 0x");
	Print::printHexa(addr);
	VgaBuffer::putstr("\n");
}
