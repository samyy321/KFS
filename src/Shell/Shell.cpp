#include "Shell.h"
#include "VgaBuffer.h"
#include "String.h"
#include "lib.h"

Shell::Shell() : cmdCount(0)
{
	for (int i = 0; i < CMD_MAX; ++i)
		commands[i] = nullptr;
}

Shell::Cmd::Cmd() : nameLen(0), argsCount(0)
{

}

void Shell::start()
{
	VgaBuffer::putstr("\n");
	VgaBuffer::putstr(PROMPT);
	while (true);
}

void Shell::writeToMemory(String& str, uint32_t addr)
{
	MemLib::memcpy((void*)addr, (char*)str, str.getSize());
}

void Shell::printBytesAsChars(uint32_t start)
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

void Shell::hexMemoryDump(uint32_t start, uint32_t end)
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

// https://wiki.osdev.org/%228042%22_PS/2_Controller
// http://aodfaq.wikidot.com/kbc-output-port
// https://wiki.osdev.org/Reboot
void Shell::reboot()
{
	uint8_t good = 0x02;

	// Poll bit 1 of the Status Register ("Input buffer empty/full") until it becomes clear.
	while (good & 0x02)
		good = readPort(0x64);

	// Set the reset line bit to 0
	writePort(0x64, 0xFE);
}

void Shell::printStroke(char strokeValue)
{
	char c[2] = {};

	c[0] = strokeValue;
	if (strokeValue == '\b')
	{
		if (bufferLen)
			VgaBuffer::eraseChar(sizeof(PROMPT) - 1);
	}
	else
	{
		VgaBuffer::putstr(&(*c));
	}
}

void Shell::addValToBuffer(char value)
{
	printStroke(value);

	if (value == '\0')
		return;
	if (value == '\n')
	{
		parseBuffer();
		VgaBuffer::putstr(PROMPT);
		return;
	}

	if (bufferLen == BUF_MAX - 2)
		bufferLen = 0;
	if (value == '\b')
	{
		if (bufferLen == 0)
			return;
		buffer[--bufferLen] = '\0';
	}
	else
	{
		buffer[bufferLen] = value;
		buffer[++bufferLen] = '\0';
	}
}

void Shell::addCommand(String *cmd)
{
	for (int i = 0; i < CMD_MAX; ++i)
	{
		if (commands[i] == nullptr)
		{
			commands[i] = cmd;
			cmdCount++;
			return;
		}
	}
	VgaBuffer::putstr("CMD_MAX is too low.");
}

bool Shell::isKnownCmd(const String& cmd)
{
	for (int i = 0; i < cmdCount; ++i)
		if (*commands[i] == cmd)
			return true;

	return false;
}

void	Shell::getCmdName(Shell::Cmd& cmd)
{
	uint16_t len = 0;

	for (;buffer[len] != '\0' && !Utils::isSpace(buffer[len]); ++len)
		cmd.name[len] = buffer[len];

	//TODO: implement this in String class to avoid the '\0' C-like coding style?
	cmd.name[len] = '\0';
	cmd.nameLen = len;
}

String Shell::Cmd::getArg(uint8_t argNb)
{
	String arg;
	int i = 0;

	if (argsCount == 0)
		return arg;

	while (argNb >= 0 && args[i])
	{
		if (args[i] == ';')
			argNb--;
		else if (argNb == 0)
			arg += args[i];
		++i;
	}
	return arg;
}

void Shell::getArgs(Shell::Cmd& cmd)
{
	uint16_t count = 0;
	int i = cmd.nameLen;
	int j = 0;
	bool isNewArg = false;

	const char argsDelimiter = ';';

	while (buffer[i] != '\0')
	{
		if (Utils::isSpace(buffer[i]))
		{
			isNewArg = true;
			++i;
			continue;
		}

		if (isNewArg)
		{
			if (count > 0)
				cmd.args[j++] = argsDelimiter;
			++count;
			isNewArg = false;
		}

		cmd.args[j] = buffer[i];
		++j;
		++i;
	}

	//TODO: implement this in String class to avoid the '\0' C-like coding style?
	cmd.args[j] = '\0';
	cmd.argsCount = count;
}

bool Shell::execCmd(Shell::Cmd& currentCmd)
{
	// TODO: better use OO design here maybe command design pattern...
	if (currentCmd.name == REBOOT)
		reboot();
	else if (currentCmd.name == GODTAKE)
	{
		VgaBuffer::putstr("Memory dump from adress ");
		Print::printHexa((uint32_t)Utils::atoi(currentCmd.getArg(0)));
		VgaBuffer::putstr(" to adress ");
		Print::printHexa((uint32_t)Utils::atoi(currentCmd.getArg(1)));
		VgaBuffer::putstr(":\n");

		hexMemoryDump((uint32_t)Utils::atoi(currentCmd.getArg(0)),
						(uint32_t)Utils::atoi(currentCmd.getArg(1)));
		VgaBuffer::putstr("\n");
	}
	else if (currentCmd.name == GODGIVE)
	{
		String userInput(currentCmd.getArg(0));
		uint32_t addr = (uint32_t)Utils::atoi(currentCmd.getArg(1));
		writeToMemory(userInput, addr);

		VgaBuffer::putstr("String: ");
		VgaBuffer::putstrColor((char*)userInput, BLACK, LIGHT_GREEN);
		VgaBuffer::putstr(" written at adress: 0x");
		Print::printHexa(addr);
		VgaBuffer::putstr("\n");
	}
}

void Shell::parseBuffer()
{
	if (buffer[0] == '\0')
		return;

	Cmd currentCmd;
	getCmdName(currentCmd);
	getArgs(currentCmd);

	if (isKnownCmd(currentCmd.name))
		execCmd(currentCmd);
	else
		VgaBuffer::putstr("Unknown Command.\n");

	clearBuffer();
}
