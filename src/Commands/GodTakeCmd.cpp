#include "GodTakeCmd.h"
#include "lib.h"

GodTakeCmd::GodTakeCmd(): Command("godtake")
{

}

void GodTakeCmd::printBytesAsChars(uint32_t start)
{
	char currentByte[2] = {};
	VgaBuffer::putstr(" ");

	VgaBuffer::putstr("|");
	for (int end = start + 16; start < end; start++)
	{
		currentByte[0] = *(uint8_t*)start;
		if ((uint8_t)currentByte[0] > 20 && (uint8_t)currentByte[0] < 127)
			VgaBuffer::putstr(&(*currentByte));
		else
			VgaBuffer::putstr(".");
	}
	VgaBuffer::putstr("|");
}

void GodTakeCmd::hexMemoryDump(uint32_t start, uint32_t end)
{
	VgaBuffer::putstr("\n");
	Print::printHexa(start);
	VgaBuffer::putstr(" ");

	for (int i = 0; start < end + i % 16; start++, i++)
	{
		Print::printHexa((uint8_t)(*(uint8_t*)start));
		if ((i + 1) % 16 == 0)
		{
			VgaBuffer::putstr(" ");
			printBytesAsChars(start - 15);
			VgaBuffer::putstr("\n");
			Print::printHexa((uint32_t)start + 1);
			VgaBuffer::putstr(" ");
		}
		for (int i = 0; i < 1000000; ++i);
	}
}

void GodTakeCmd::exec()
{
	VgaBuffer::putstr("Memory dump from adress ");
	Print::printHexa((uint32_t)Utils::atoi(getArg(0)));
	VgaBuffer::putstr(" to adress ");
	Print::printHexa((uint32_t)Utils::atoi(getArg(1)));
	VgaBuffer::putstr(":\n");

	hexMemoryDump((uint32_t)Utils::atoi(getArg(0)),
					(uint32_t)Utils::atoi(getArg(1)));
	VgaBuffer::putstr("\n");
}
