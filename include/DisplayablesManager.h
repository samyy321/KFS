#ifndef DISPLAYABLESMANAGER_H
#define DISPLAYABLESMANAGER_H

#include "types.h"

#define BUF_MAX				4096
#define DISPLAYABLES_COUNT	1

class IDisplayable
{
public:
	virtual void addValToBuffer(char value);

protected:
	char		buffer[BUF_MAX];
	uint16_t	bufferLen;

	virtual void parseBuffer() = 0;

public:
	uint16_t getBufferLen()
	{
		return bufferLen;
	}
};

class DisplayablesManager
{
public:
	DisplayablesManager();

	void addDisplayable(IDisplayable *newDisplayable);

private:
	uint32_t displayablesCount;

public:
	IDisplayable* displayables[DISPLAYABLES_COUNT];
};

#endif
