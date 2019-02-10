#ifndef DISPLAYABLESMANAGER_H
#define DISPLAYABLESMANAGER_H

#include "types.h"

#define BUF_MAX				4096
#define DISPLAYABLES_MAX	1

// Abstract class with methods used by classes that will
// display the result of user interactions to standard output.
class Displayable
{
public:
	virtual void addValToBuffer(char value);
	virtual void clearBuffer();

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

// Class to handle the displayables as a collection.
class DisplayablesManager
{
public:
	DisplayablesManager();

	void addDisplayable(Displayable *newDisplayable);

private:
	uint32_t displayablesCount;

public:
	// TODO: implement vector when memory management ok ?
	Displayable* displayables[DISPLAYABLES_MAX];

	uint32_t getDisplayablesCount() const
	{
		return displayablesCount;
	}
};

#endif
