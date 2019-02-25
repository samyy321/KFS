#ifndef DISPLAYABLESMANAGER_H
#define DISPLAYABLESMANAGER_H

#include "types.h"

class String;

#define BUF_MAX				4096

// Abstract class with methods used by classes that will
// display the result of user interactions to standard output.
class Displayable
{
public:
	virtual void addValToBuffer(char value);
	virtual void clearBuffer();

protected:
	char		m_buffer[BUF_MAX];
	uint16_t	m_bufferLen;

	virtual void parseBuffer() = 0;

public:
	uint16_t getBufferLen()
	{
		return m_bufferLen;
	}
};

// Class to handle the displayables as a collection.
class DisplayablesManager
{
public:
	DisplayablesManager();

	void addDisplayable(Displayable *newDisplayable);

private:
	uint32_t m_displayablesCount;
	static const uint8_t m_displayablesMax = 1;

public:
	// TODO: implement vector when memory management ok ?
	Displayable* m_displayables[m_displayablesMax];

	uint32_t getDisplayablesCount() const
	{
		return m_displayablesCount;
	}
};

#endif
