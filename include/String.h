#ifndef STRING_H
#define STRING_H

#define MAX_CONTENT 64

#include "types.h"

class String
{
private:
	uint32_t size;
	char content[MAX_CONTENT]; //TODO: handle resize after implementing memory management

public:
	String(const char *str);
	String(const String& str);
	String();

	uint32_t getSize() const
	{
		return size;
	}

	char operator[](int idx) const
	{
		//TODO: implement assert
		if (idx < 0 || idx >= MAX_CONTENT)
		{
				VgaBuffer::putstr("Out of string buffer!");
				return content[0];
		}
		return content[idx];
	}

	// This overload is used for assignement
	char& operator[](int idx)
	{
		//TODO: implement assert
		if (idx < 0 || idx >= MAX_CONTENT)
		{
				VgaBuffer::putstr("Out of string buffer!");
				return content[0];
		}
		return content[idx];
	}

	String& operator=(const char* right);
	String& operator=(const String& right);
	bool operator==(const String& right);
	bool operator==(const char *right);
};

#endif
