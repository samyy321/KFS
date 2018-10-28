#ifndef VGA_BUFFER_H
#define VGA_BUFFER_H

#include "types.h"
#include "portIO.h"

//Vga buffer dimensions
#define WIDTH		80
#define HEIGHT		25

#define TAB_WIDTH	4

//Cursor index in vga buffer
#define CURRENT_IDX(currentX, currentY) currentY * WIDTH + currentX

//Non printable chars
#define BACKSPACE(currentX) if (currentX > 0) currentX--;
#define NEWLINE(currentX, currentY) currentX = 0; currentY++;
#define CARRIAGE_RET(currentX) currentX = 0;
#define TAB(currentX, currentY) currentX += TAB_WIDTH - (currentX % TAB_WIDTH);

//Put values to Vga buffer
#define PUTC(c, currentVal) currentVal = (currentVal & 0xFF00) | c
#define PUT_BCOLOR(color, currentVal) currentVal = (currentVal & 0x0FFF) | (color << 12)
#define PUT_FCOLOR(color, currentVal) currentVal = (currentVal & 0xF0FF) | (color << 8)

//Colors
#define BLACK			0
#define BLUE			1
#define GREEN			2
#define CYAN			3
#define RED				4
#define MAGENTA			5
#define BROWN			6
#define LIGHT_GREY		7
#define DARK_GREY		8
#define LIGHT_BLUE		9
#define LIGHT_GREEN		10
#define LIGHT_CYAN		11
#define LIGHT_RED		12
#define LIGHT_MAGENTA	13
#define LIGHT_BROWN		14
#define WHITE			15

namespace	VgaBuffer
{
	extern unsigned short	*base;
	extern unsigned int		currentY;
	extern unsigned int		currentX;

	void	putstr(const char *str);
	void	putstrColor(const char *str, int8_t backColor, int8_t frontColor);
	void	scroll(void);
	void	clear(void);
	void	updateCursor(unsigned short pos);
	void 	enableCursor(uint8_t cursorStart, uint8_t cursorEnd);
}

#endif
