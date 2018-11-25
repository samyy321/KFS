#include "String.h"
#include "VgaBuffer.h"

String::String()
{

}

String::String(const char *str)
{
	*this = str;
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
	size = --i;
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
	size = --i;
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
