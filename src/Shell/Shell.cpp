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
		if (commands[i] == nullptr)
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

void	Shell::getCmdName(Shell::Cmd& cmd)
{
	uint16_t len;

	for (len = 0; buffer[len] != '\0' && !Utils::isSpace(buffer[len]); ++len)
		cmd.name[len] = buffer[len];

	//TODO: implement this in String class to avoid the '\0' C-like coding style?
	cmd.name[len] = '\0';
	cmd.nameLen = len;
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
	if (currentCmd.name == REBOOT)
		reboot();
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
