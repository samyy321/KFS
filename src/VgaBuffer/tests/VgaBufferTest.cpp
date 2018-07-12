#include "VgaBuffer.h"

namespace	VgaBuffer
{
	unsigned short	*base = (unsigned short *)0xb8000;
	unsigned int	current_ypos;
	unsigned int	current_xpos;
}
