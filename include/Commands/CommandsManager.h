#ifndef CMD_MNGR_H
#define CMD_MNGR_H

#include "String.h"

class Command
{
protected:
	Command(String&& cmdName);

private:
	String name;
	String args;
	uint16_t nameLen;
	uint8_t argsCount;

	const char argsDelimiter = ';';

public:
	String getArg(uint8_t argNb);
	void addArg(const String& arg);
	void clearArgs();
	virtual void exec() = 0;

	String getName() const
	{
		return name;
	}
};

// Class to handle the commands as a collection.
class CommandsManager
{
public:
	CommandsManager();

private:
	static const uint8_t cmdMax = 5;
	uint8_t cmdCount;
	Command* commands[cmdMax];

public:
	void addCommand(Command* cmd);
	Command* getCommand(const String& cmdName) const;
};

#endif
