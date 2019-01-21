#ifndef LIB_H
#define LIB_H

#include "types.h"

class String;

namespace	MemLib
{
	void	*memcpy(void *dst, const void *src, uint32_t n);
}

namespace Utils
{
	bool	isSimpleSpace(char c);
	bool	isSpace(char c);
	bool	isascii(int c);
	int		atoi(const String str);
	int		strlen(const char *s);
}

namespace Print
{
	void	printHexa(uint8_t nb);
	void	printHexa(uint32_t nb);
}

#endif
