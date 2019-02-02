#ifndef DISPLAYABLESMANAGER_H
#define DISPLAYABLESMANAGER_H

#include "types.h"

#define BUF_MAX				4096
#define DISPLAYABLES_COUNT	1

// Abstract class with methods used by classes that will
// display the result of user interactions to standard output.
class Displayable
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

// Class to handle a the displayables as a collection.
class DisplayablesManager
{
public:
	DisplayablesManager();

	void addDisplayable(Displayable *newDisplayable);

private:
	uint32_t displayablesCount;

public:
	Displayable* displayables[DISPLAYABLES_COUNT];
};

#endif
