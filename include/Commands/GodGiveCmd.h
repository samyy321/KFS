#ifndef GODGIVECMD_H
#define GODGIVECMD_H

#include "String.h"
#include "CommandsManager.h"

class GodGiveCmd : public Command
{
public:
	GodGiveCmd();
	virtual void exec() override;

private:
	void writeToMemory(String& str, uint32_t addr);
};

#endif
