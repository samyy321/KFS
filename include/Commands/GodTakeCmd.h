#ifndef GODTAKECMD_H
#define GODTAKECMD_H

#include "types.h"
#include "String.h"
#include "CommandsManager.h"

class GodTakeCmd : public Command
{
public:
	GodTakeCmd();
	virtual void exec() override;

private:
	void printBytesAsChars(uint32_t start);
	void hexMemoryDump(uint32_t start, uint32_t end);
};

#endif
