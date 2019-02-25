#ifndef CMD_MNGR_H
#define CMD_MNGR_H

#include "String.h"

class Command
{
protected:
	Command(String&& cmdName);

private:
	String m_name;
	String m_args;
	uint16_t m_nameLen;
	uint8_t m_argsCount;

	const char m_argsDelimiter = ';';

public:
	String getArg(uint8_t argNb);
	void addArg(const String& arg);
	void clearArgs();
	virtual void exec() = 0;

	String getName() const
	{
		return m_name;
	}
};

// Class to handle the commands as a collection.
class CommandsManager
{
public:
	CommandsManager();

private:
	static const uint8_t m_cmdMax = 5;
	uint8_t m_cmdCount;
	Command* m_commands[m_cmdMax];

public:
	void addCommand(Command* cmd);
	Command* getCommand(const String& cmdName) const;
};

#endif
