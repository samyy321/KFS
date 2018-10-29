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
	String(char *str);
	String(String& str);
	String();

	uint32_t getSize() const
	{
		return size;
	}

	char operator[](int idx) const
	{
		return content[idx];
	}

	String& operator=(const char* right);
	String& operator=(const String& right);
	bool operator==(const String& right);
	bool operator==(const char *right);
};

#endif
