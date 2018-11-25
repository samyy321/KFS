#include "types.h"
#include "VgaBuffer.h"

namespace Print
{
	void	printHexa(uint8_t nb)
	{
		char* hex = "0123456789ABCDEF";
		char* res = "00";

		res[0] = hex[(nb >> 4) & 0x0F];
		res[1] = hex[nb & 0x0F];
		VgaBuffer::putstr(&res[0]);
	}

	void	printHexa(uint32_t nb)
	{
		printHexa((uint8_t)(nb >> 24));
		printHexa((uint8_t)(nb >> 16));
		printHexa((uint8_t)(nb >> 8));
		printHexa((uint8_t)(nb & 0xFF));
	}
}
