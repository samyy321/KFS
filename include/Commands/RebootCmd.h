#ifndef REBOOTCMD_H
#define REBOOTCMD_H

#include "String.h"
#include "CommandsManager.h"

class RebootCmd : public Command
{
public:
	RebootCmd();
	virtual void exec() override;
};

#endif
