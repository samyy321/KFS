#ifndef IDT_H
#define IDT_H

#include "InterruptDescriptorTable.h"
#include "types.h"

class	InterruptDescriptorTable
{
public:
	class	InterruptDescriptor
	{
	private:
		uint16_t	base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
		uint16_t	sel;                 // Kernel segment selector.
		uint8_t		always0;             // This must always be zero.
		uint8_t		flags;               // More flags. See documentation.
	 	uint16_t	base_hi;             // The upper 16 bits of the address to jump to.
	public:
		InterruptDescriptor(uint32_t base, uint16_t sel, uint8_t flags);

	}__attribute__((packed));

public:
	InterruptDescriptorTable();
};

#endif
