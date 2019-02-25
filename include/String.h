#ifndef STRING_H
#define STRING_H

#define MAX_CONTENT 64

#include "types.h"
#include "VgaBuffer.h"
#include "lib.h"

class String
{
private:
	char m_content[MAX_CONTENT]; //TODO: handle resize after implementing memory management
	size_t m_length;

public:
	String(const char *str);
	String(const String& str);
	String();
	void clear();
	void pushBack(char c);
	void pushBack(const String& str);

	uint32_t getSize() const
	{
		return m_length;
	}

	const char& operator[](int idx) const
	{
		//TODO: implement assert
		if (idx < 0 || idx >= MAX_CONTENT)
		{
				VgaBuffer::putstr("const char& operator[]: Out of string buffer!\n");
				return m_content[0];
		}
		return m_content[idx];
	}

	// This overload is used for assignement
	char& operator[](int idx)
	{
		//TODO: implement assert
		if (idx < 0 || idx >= MAX_CONTENT)
		{
				VgaBuffer::putstr("char& operator[]: Out of string buffer!\n");
				return m_content[0];
		}
		return m_content[idx];
	}

	operator char*(){return &m_content[0];}

	String& operator=(const char* right);
	String& operator=(const String& right);
	bool operator==(const String& right);
	bool operator==(const char *right);
	String& operator+=(char c);
	String& operator+=(const String& right);
};

#endif
