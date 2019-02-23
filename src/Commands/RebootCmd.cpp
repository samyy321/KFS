#include "RebootCmd.h"

RebootCmd::RebootCmd() : Command("reboot")
{

}

// https://wiki.osdev.org/%228042%22_PS/2_Controller
// http://aodfaq.wikidot.com/kbc-output-port
// https://wiki.osdev.org/Reboot
void RebootCmd::exec()
{
	uint8_t good = 0x02;

	// Poll bit 1 of the Status Register ("Input buffer empty/full") until it becomes clear.
	while (good & 0x02)
		good = readPort(0x64); //TODO: where this method come from

	// Set the reset line bit to 0
	writePort(0x64, 0xFE); //TODO: where this method come from
}
