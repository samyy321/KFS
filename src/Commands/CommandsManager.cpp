#include "CommandsManager.h"

CommandsManager::CommandsManager() : cmdCount(0)
{
	for (int i = 0; i < CommandsManager::cmdMax; ++i)
		commands[i] = nullptr;
}

void CommandsManager::addCommand(Command *cmd)
{
	if (cmdCount == CommandsManager::cmdMax)
	{
		VgaBuffer::putstr("CommandsManager::cmdMax is too low.");
		return;
	}
	commands[cmdCount] = cmd;
	cmdCount++;
}

Command* CommandsManager::getCommand(const String& cmdName) const
{
	for (int i = 0; i < cmdCount; ++i)
	{
		if (commands[i]->getName() == cmdName)
			return commands[i];
	}
	return nullptr;
}

Command::Command(String&& cmdName) : name(cmdName), argsCount(0)
{

}

void Command::addArg(const String& arg)
{
	args += arg;
	args += argsDelimiter;
	argsCount++;
}

void Command::clearArgs()
{
	args = "";
	argsCount = 0;
}

String Command::getArg(uint8_t argNb)
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
