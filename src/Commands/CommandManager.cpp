#include "CommandManager.h"

CommandManager::CommandManager()
{
	for (int i = 0; i < CommandManager::cmdMax; ++i)
		commands[i] = nullptr;
}

void CommandManager::addCommand(Command *cmd)
{
	if (cmdCount == CommandManager::cmdMax)
	{
		VgaBuffer::putstr("CommandManager::cmdMax is too low.");
		return;
	}
	commands[cmdCount - 1] = cmd;
	cmdCount++;
}

void CommandManager::execCmd(const String& cmdName)
{
	for (int i = 0; i < cmdCount; ++i)
	{
		if (commands[i]->getName() == cmdName)
		{
			commands[i]->exec();
			return;
		}
	}
	VgaBuffer::putstr("Unknown Command.\n");
}
