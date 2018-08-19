#include "lib.h"

namespace	MemLib
{
	void		*memcpy(void *dst, const void *src, uint32_t n)
	{
		uint32_t i;

		i = 0;
		while (i < n)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
		return (dst);
	}
}
