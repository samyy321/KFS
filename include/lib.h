#ifndef LIB_H
#define LIB_H

#include "types.h"

namespace	MemLib
{
	void	*memcpy(void *dst, const void *src, uint32_t n);
}

namespace Utils
{
	bool	isSimpleSpace(char c);
	bool	isSpace(char c);
}

namespace Print
{
	void	printHexa(uint8_t nb);
	void	printHexa(uint32_t nb);
}

#endif
