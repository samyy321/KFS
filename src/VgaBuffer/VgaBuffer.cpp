#include "VgaBuffer.h"

namespace	VgaBuffer
{
	unsigned short	*base = (unsigned short *)0xb8000;
	unsigned int	current_ypos;
	unsigned int	current_xpos;

	void	scroll(void)
	{
		int i, j;

		for(i = 0; i < HEIGHT; i++) {
			for (j = 0; j < WIDTH; j++) {
				VgaBuffer::base[i * WIDTH + j] = VgaBuffer::base[(i + 1) * WIDTH + j];
			}
		}
		VgaBuffer::current_ypos = HEIGHT - 1;
	}

	void	putchar(char c)
	{
		int	current_pos;

		current_pos = VgaBuffer::current_ypos * WIDTH + VgaBuffer::current_xpos;
		VgaBuffer::base[current_pos] = (VgaBuffer::base[current_pos] & 0xFF00) | c;
		VgaBuffer::current_xpos++;
	}

	void	putstr(char *str)
	{
		char	c;

		while ((c = *str++) != '\0') {
			if (VgaBuffer::current_ypos >= HEIGHT)
				scroll();
			if (c == '\b') {
				BACKSPACE(VgaBuffer::current_xpos)
			} else if (c == '\r') {
				CARRIAGE_RET(VgaBuffer::current_xpos)
			} else
				if (c == '\n') {
					NEWLINE(VgaBuffer::current_xpos, VgaBuffer::current_ypos)
				} else {
					if (VgaBuffer::current_xpos >= WIDTH) {
						VgaBuffer::current_xpos = 0;
						VgaBuffer::current_ypos++;
					}
					putchar(c);
				}
		}
	}
}
