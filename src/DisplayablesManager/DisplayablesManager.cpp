#include "DisplayablesManager.h"

// A displayable has a buffer for storing keystrokes
void Displayable::addValToBuffer(char value)
{
	//TODO: Implement growing buffer
	if (m_bufferLen == BUF_MAX - 2)
		m_bufferLen = 0;
	m_buffer[m_bufferLen] = value;
	m_buffer[++m_bufferLen] = '\0';
}

void Displayable::clearBuffer()
{
	int i = 0;

	for (int i = 0; i < BUF_MAX; ++i)
		m_buffer[i] = '\0';
	m_bufferLen = 0;
}

DisplayablesManager::DisplayablesManager() : m_displayablesCount(0)
{

}

void DisplayablesManager::addDisplayable(Displayable* newDisplayable)
{
	m_displayables[m_displayablesCount] = newDisplayable;
	m_displayablesCount++;
}
