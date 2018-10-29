#include "KbdHandler.h"
#include "InterruptsManager.h"
#include "VgaBuffer.h"

bool KbdHandler::shiftPressed = false;

KbdHandler::KbdHandler(InterruptsManager *intManager, DisplayablesManager *displayablesManager) : InterruptHandler(0x21, intManager)
{
	this->displayablesManager = displayablesManager;
	while (readPort(CMD_PORT) & 0x01)
		readPort(DATA_PORT);
	writePort(CMD_PORT, 0xAE); // Enable first PS/2 port
	writePort(CMD_PORT, 0x20); // Read PS/2 Controller Configuration Byte (give me your current state command)
	uint8_t status = (readPort(DATA_PORT) | 1) & ~0x10; // Read the state and change it to enable interrupts (bit 0) and keyboard (bit 4) https://www.win.tue.nl/~aeb/linux/kbd/scancodes-11.html#kccb5
	writePort(CMD_PORT, 0x60);
	writePort(DATA_PORT, status); // Write new status
	writePort(DATA_PORT, 0x80);
}

KbdHandler::Keystroke::Keystroke(uint8_t scancode)
{
	keycode = scancode & KBD_SCANCODE_MASK;
	isPressed = (scancode & KBD_STATUS_MASK) >> 7;

	if (keycode == LSHIFT_CODE || keycode == RSHIFT_CODE)
		KbdHandler::shiftPressed = !isPressed;

	char firstChr = us_keymap[keycode][0][0];
	isPrintable = firstChr && firstChr != 'F' && firstChr != '_';
	setAsciiVal();
}

void KbdHandler::Keystroke::setAsciiVal()
{
	switch (keycode) {
	case BS_CODE :
		asciiVal = 8;
		break;
	case HT_CODE :
		asciiVal = 9;
		break;
	case NL_CODE :
		asciiVal = 10;
		break;
	case ESC_CODE:
		asciiVal = 27;
		break;
	case SP_CODE:
		asciiVal = 32;
		break;
	default:
		asciiVal = !isPrintable ? 0 : us_keymap[keycode][shiftPressed][0];
	}
}

void KbdHandler::Keystroke::printAsciiVal()
{
	char asciiValToStr[2];

	asciiValToStr[0] = asciiVal;
	asciiValToStr[1] = '\0';
	if (!isPressed)
		VgaBuffer::putstr(&asciiValToStr[0]);
}

uint32_t KbdHandler::execInterruptRoutine(uint32_t esp)
{
	Keystroke key(readPort(0x60));
	if (!key.getState())
		for (int i = 0; i < DISPLAYABLES_COUNT; i++)
			displayablesManager->displayables[i]->addValToBuffer(key.getAsciiVal());
	return esp;
}
