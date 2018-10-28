#include "DisplayablesManager.h"

// A displayable has a buffer for storing keystrokes
void IDisplayable::addValToBuffer(char value)
{
	//TODO: Implement growing buffer
	if (bufferLen == BUF_MAX - 2)
		bufferLen = 0;
	buffer[bufferLen] = value;
	buffer[++bufferLen] = '\0';
}

DisplayablesManager::DisplayablesManager() : displayablesCount(0)
{

}

void DisplayablesManager::addDisplayable(IDisplayable* newDisplayable)
{
	displayables[displayablesCount] = newDisplayable;
	displayablesCount++;
}
