#include "Shell.h"
#include "VgaBuffer.h"
#include "String.h"
#include "lib.h"
#include "CommandsManager.h"

Shell::Shell(CommandsManager* cmdManager) : m_cmdManager(cmdManager)
{

}

void Shell::start()
{
	VgaBuffer::putstr("\n");
	VgaBuffer::putstr(PROMPT);
	while (true);
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

String	Shell::parseCmdName()
{
	String cmdName = "";

	for (uint8_t i = 0; buffer[i] != '\0' && !Utils::isSpace(buffer[i]); ++i)
		cmdName += buffer[i];

	return cmdName;
}

void Shell::setArgsToCmd(Command& cmd)
{
	cmd.clearArgs();
	String currentArg;

	for (int i = cmd.getName().getSize() + 1; buffer[i]; ++i)
	{
		if (Utils::isSpace(buffer[i]))
		{
			cmd.addArg(currentArg);
			currentArg = "";
		}
		else
		{
			currentArg += buffer[i];
		}
	}
	cmd.addArg(currentArg);
}

void Shell::parseBuffer()
{
	if (buffer[0] == '\0')
		return;

	Command* currentCmd = m_cmdManager->getCommand(parseCmdName());
	if (currentCmd)
	{
		setArgsToCmd(*currentCmd);
		currentCmd->exec();
	}
	else
	{
		VgaBuffer::putstr("Unknown Command.\n");
	}

	clearBuffer();
}
