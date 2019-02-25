#include "String.h"
#include "VgaBuffer.h"
#include "lib.h"

String::String()
: m_length(0)
{
	clear();
}

String::String(const String& str)
{
	operator=(str);
}

String::String(const char* str)
{
	operator=(str);
}

// TODO: handle m_content larger than buffer size
String& String::operator=(const char* right)
{
	int i = 0;
	while (right[i] != '\0' && i < MAX_CONTENT - 1)
	{
		m_content[i] = right[i];
		++i;
	}
	m_content[i] = '\0';
	m_length = Utils::strlen(right);

	return *this;
}

String& String::operator=(const String& right)
{
	int i = 0;
	while (right[i] != '\0' && i < MAX_CONTENT - 1)
	{
		m_content[i] = right[i];
		++i;
	}
	m_content[i] = '\0';
	m_length = right.getSize();

	return *this;
}

bool String::operator==(const String& right)
{
	int i = 0;
	while (m_content[i] && m_content[i] == right[i])
		++i;

	return ((m_content[i] - right[i]) == 0);
}

bool String::operator==(const char* right)
{
	int i = 0;
	while (m_content[i] && m_content[i] == right[i])
		++i;

	return ((m_content[i] - right[i]) == 0);
}

String& String::operator+=(char c)
{
	pushBack(c);
	return *this;
}

String& String::operator+=(const String& right)
{
	pushBack(right);
	return *this;
}

void String::pushBack(char c)
{
	const size_t newLength = m_length + 1;
	if (newLength + 1 >= MAX_CONTENT)
	{
		// TODO: implement resize
		VgaBuffer::putstr("pushBack: Out of string buffer!\n");
		return;
	}
	m_content[m_length] = c;
	m_content[newLength] = '\0';
	m_length = newLength;
}

void String::pushBack(const String& str)
{
	const size_t newLength = m_length + str.getSize();
	if (newLength + 1 >= MAX_CONTENT)
	{
		// TODO: implement resize
		VgaBuffer::putstr("pushBack: Out of string buffer!\n");
		return;
	}

	for (int i = m_length, j = 0; str[j]; ++i, ++j)
		m_content[i] = str[j];

	m_content[newLength] = '\0';
	m_length = newLength;
}

void String::clear()
{
	int i = 0;

	while (i < MAX_CONTENT)
	{
		m_content[i] = '\0';
		++i;
	}
}
