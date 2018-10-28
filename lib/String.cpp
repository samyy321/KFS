#include "String.h"
#include "VgaBuffer.h"

String::String()
{

}

String::String(char *str)
{
	*this = str;
}

// TODO: handle content larger than buffer size
String& String::operator=(const char* right)
{
	int i = 0;
	while (right[i] != '\0')
	{
		content[i] = right[i];
		++i;
	}
	size = --i;
}

bool String::operator==(String const& right)
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
