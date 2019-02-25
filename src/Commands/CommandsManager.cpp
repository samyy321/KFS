#include "CommandsManager.h"

CommandsManager::CommandsManager() : m_cmdCount(0)
{
	for (int i = 0; i < CommandsManager::m_cmdMax; ++i)
		m_commands[i] = nullptr;
}

void CommandsManager::addCommand(Command *cmd)
{
	if (m_cmdCount == CommandsManager::m_cmdMax)
	{
		VgaBuffer::putstr("CommandsManager::cmdMax is too low.");
		return;
	}
	m_commands[m_cmdCount] = cmd;
	m_cmdCount++;
}

Command* CommandsManager::getCommand(const String& cmdName) const
{
	for (int i = 0; i < m_cmdCount; ++i)
	{
		if (m_commands[i]->getName() == cmdName)
			return m_commands[i];
	}
	return nullptr;
}

Command::Command(String&& cmdName) : m_name(cmdName), m_argsCount(0)
{

}

void Command::addArg(const String& arg)
{
	m_args += arg;
	m_args += m_argsDelimiter;
	m_argsCount++;
}

void Command::clearArgs()
{
	m_args = "";
	m_argsCount = 0;
}

String Command::getArg(uint8_t argNb)
{
	String arg;
	int i = 0;

	if (m_argsCount == 0)
		return arg;

	while (argNb >= 0 && m_args[i])
	{
		if (m_args[i] == ';')
			argNb--;
		else if (argNb == 0)
			arg += m_args[i];
		++i;
	}
	return arg;
}
