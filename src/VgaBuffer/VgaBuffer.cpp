#include "VgaBuffer.h"

namespace	VgaBuffer
{
	unsigned short	*base = (unsigned short *)0xb8000;
	unsigned int	currentY;
	unsigned int	currentX;

	void	scroll(void)
	{
		int i, j;

		for (i = 0; i < HEIGHT; i++) {
			for (j = 0; j < WIDTH; j++) {
				VgaBuffer::base[i * WIDTH + j] = VgaBuffer::base[(i + 1) * WIDTH + j];
			}
		}
		VgaBuffer::currentY = HEIGHT - 1;
	}

	// Cursor registers: http://web.stanford.edu/class/cs140/projects/pintos/specs/freevga/vga/crtcreg.htm
	// https://wiki.osdev.org/Text_Mode_Cursor
	// Set the CRTC adress register to cursor start/end and set only
	// the Cursor Scan Line Start/End bits in the data registers
	void enableCursor(uint8_t cursorStart, uint8_t cursorEnd)
	{
		writePort(0x3D4, 0x0A);
		writePort(0x3D5, (readPort(0x3D5) & 0xC0) | cursorStart);

		writePort(0x3D4, 0x0B);
		writePort(0x3D5, (readPort(0x3D5) & 0xE0) | cursorEnd);
	}

	// Set the CRTC adress register to cursor location low/high
	// and set the new location in the data registers
	void	updateCursor(unsigned short pos)
	{
		writePort(0x3D4, 0x0F);
		writePort(0x3D5, (unsigned char) (pos & 0xFF));
		writePort(0x3D4, 0x0E);
		writePort(0x3D5, (unsigned char) ((pos >> 8) & 0xFF));
	}

	void	clear(void)
	{
		unsigned int i;

		VgaBuffer::currentX = 0;
		VgaBuffer::currentY = 0;
		for (i = 0; i < HEIGHT * WIDTH; i++) {
			PUTC(' ', VgaBuffer::base[i]);
			PUT_BCOLOR(BLACK, VgaBuffer::base[i]);
		}
	}

	void	eraseChar(uint8_t minX)
	{
		if (VgaBuffer::currentX == 0)
		{
			VgaBuffer::currentX = WIDTH - 1;
			VgaBuffer::currentY--;
		}
		else
		{
			VgaBuffer::currentX--;
		}

		updateCursor(CURRENT_IDX(VgaBuffer::currentX, VgaBuffer::currentY));
		PUTC(' ', VgaBuffer::base[CURRENT_IDX(VgaBuffer::currentX,
											VgaBuffer::currentY)]);
	}

	void	putstr(const char *str)
	{
		char	c;

		while ((c = *str++) != '\0')
		{
			if (VgaBuffer::currentY >= HEIGHT)
				scroll();

			switch (c)
			{
			case '\b':
				BACKSPACE(VgaBuffer::currentX)
				break;
			case '\r':
				CARRIAGE_RET(VgaBuffer::currentX)
				break;
			case '\n':
				NEWLINE(VgaBuffer::currentX, VgaBuffer::currentY)
				scroll();
				break;
			default:
				if (VgaBuffer::currentX >= WIDTH)
				{
					NEWLINE(VgaBuffer::currentX, VgaBuffer::currentY)
					scroll();
				}

				if (c == '\t')
				{
					TAB(VgaBuffer::currentX, VgaBuffer::currentY)
				}
				else
				{
					PUTC(c, VgaBuffer::base[CURRENT_IDX(VgaBuffer::currentX,
														VgaBuffer::currentY)]);
					VgaBuffer::currentX++;
				}
				break;
			}
		}

		updateCursor(CURRENT_IDX(VgaBuffer::currentX, VgaBuffer::currentY));
	}

	void	putstrColor(const char *str, int8_t backColor, int8_t frontColor)
	{
		char	c;

		while ((c = *str++) != '\0') {
			if (VgaBuffer::currentY >= HEIGHT)
				scroll();
			if (c == '\b') {
				BACKSPACE(VgaBuffer::currentX)
			} else if (c == '\r') {
				CARRIAGE_RET(VgaBuffer::currentX)
			} else if (c == '\n') {
				NEWLINE(VgaBuffer::currentX, VgaBuffer::currentY)
				scroll();
			} else {
				if (VgaBuffer::currentX >= WIDTH) {
					NEWLINE(VgaBuffer::currentX, VgaBuffer::currentY)
					scroll();
				} if (c == '\t')
					TAB(VgaBuffer::currentX, VgaBuffer::currentY)
				else {
					PUTC(c, VgaBuffer::base[CURRENT_IDX(VgaBuffer::currentX,
														VgaBuffer::currentY)]);
					PUT_BCOLOR(backColor,
						 		VgaBuffer::base[CURRENT_IDX(VgaBuffer::currentX,
														VgaBuffer::currentY)]);
					PUT_FCOLOR(frontColor,
								VgaBuffer::base[CURRENT_IDX(VgaBuffer::currentX,
														VgaBuffer::currentY)]);
					VgaBuffer::currentX++;
				}
			}
		}
		updateCursor(CURRENT_IDX(VgaBuffer::currentX, VgaBuffer::currentY));
	}
}
