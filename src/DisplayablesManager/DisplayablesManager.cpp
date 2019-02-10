#include "DisplayablesManager.h"

// A displayable has a buffer for storing keystrokes
void Displayable::addValToBuffer(char value)
{
	//TODO: Implement growing buffer
	if (bufferLen == BUF_MAX - 2)
		bufferLen = 0;
	buffer[bufferLen] = value;
	buffer[++bufferLen] = '\0';
}

void Displayable::clearBuffer()
{
	int i = 0;

	for (int i = 0; i < BUF_MAX; ++i)
		buffer[i] = '\0';
	bufferLen = 0;
}

DisplayablesManager::DisplayablesManager() : displayablesCount(0)
{

}

void DisplayablesManager::addDisplayable(Displayable* newDisplayable)
{
	displayables[displayablesCount] = newDisplayable;
	displayablesCount++;
}
