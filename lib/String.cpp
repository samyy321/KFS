#include "String.h"
#include "VgaBuffer.h"
#include "lib.h"

String::String()
: length(0)
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

// TODO: handle content larger than buffer size
String& String::operator=(const char* right)
{
	int i = 0;
	while (right[i] != '\0' && i < MAX_CONTENT - 1)
	{
		content[i] = right[i];
		++i;
	}
	content[i] = '\0';
	length = Utils::strlen(right);

	return *this;
}

String& String::operator=(const String& right)
{
	int i = 0;
	while (right[i] != '\0' && i < MAX_CONTENT - 1)
	{
		content[i] = right[i];
		++i;
	}
	content[i] = '\0';
	length = right.getSize();

	return *this;
}

bool String::operator==(const String& right)
{
	int i = 0;
	while (content[i] && content[i] == right[i])
		++i;

	return ((content[i] - right[i]) == 0);
}

bool String::operator==(const char* right)
{
	int i = 0;
	while (content[i] && content[i] == right[i])
		++i;

	return ((content[i] - right[i]) == 0);
}

String& String::operator+=(char c)
{
	pushBack(c);
	return *this;
}

void String::clear()
{
	int i = 0;

	while (i < MAX_CONTENT)
	{
		content[i] = '\0';
		++i;
	}
}

void String::pushBack(char c)
{
	const size_t newLength = length + 1;
	if (newLength + 1 >= MAX_CONTENT)
	{
		// TODO: implement resize
		VgaBuffer::putstr("pushBack: Out of string buffer!\n");
		return;
	}
	content[length] = c;
	content[newLength] = '\0';
	length = newLength;
}
