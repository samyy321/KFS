#ifndef VGA_BUFFER_H
#define VGA_BUFFER_H

#define WIDTH	80
#define HEIGHT	25

#define BACKSPACE(current_xpos) if (current_xpos > 0) current_xpos--;
#define NEWLINE(current_xpos, current_ypos) current_xpos = 0; current_ypos++;
#define CARRIAGE_RET(current_xpos) current_xpos = 0;

namespace	VgaBuffer
{
	extern unsigned short	*base;
	extern unsigned int		current_ypos;
	extern unsigned int		current_xpos;

	void	putchar(char c);
	void	putstr(char *str);
	void	scroll(void);
}

#endif
