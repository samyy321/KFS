#include "Shell.h"
#include "VgaBuffer.h"
#include "String.h"
#include "lib.h"

Shell::Shell()
{
	for (int i = 0; i < NB_CMD; ++i)
		commands[i] = 0;
}

void Shell::start()
{
	VgaBuffer::putstr("\n");
	VgaBuffer::putstr(PROMPT);
	while (true);
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
	char* c = "\0";

	c[0] = strokeValue;
	if (strokeValue == '\b')
	{
		if (bufferLen)
			VgaBuffer::eraseChar(sizeof(PROMPT) - 1);
	}
	else
	{
		VgaBuffer::putstr(c);
	}
}

void Shell::addValToBuffer(char value)
{
	printStroke(value);

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
	for (int i = 0; i < NB_CMD; ++i)
	{
		if (commands[i] == 0)
		{
			commands[i] = cmd;
			return;
		}
	}
}

bool Shell::isKnownCmd(const String& cmd)
{
	for (int i = 0; i < NB_CMD; ++i)
		if (*commands[i] == cmd)
			return true;

	return false;
}

bool Shell::execCmd(String& cmd)
{
	if (cmd == REBOOT)
		reboot();
}

void Shell::parseBuffer()
{
	if (buffer[0] == '\0')
		return;

	String cmd(buffer);
	if (isKnownCmd(cmd))
		execCmd(cmd);
	else
		VgaBuffer::putstr("Unknown Command.\n");

	buffer[0] = '\0';
	bufferLen = 0;
}
