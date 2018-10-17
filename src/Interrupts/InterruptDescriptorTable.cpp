#include "InterruptDescriptorTable.h"

InterruptDescriptorTable::InterruptDescriptorTable()
: nullSegment(0, 0, 0, 0),
KernCodeSegment(0, 0xFFFFFFFF, KERN_CODE_FLAG, 0xCF),
KernStackSegment(0, 0xFFFFFFFF, KERN_STACK_FLAG, 0xCF),
KernDataSegment(0, 0xFFFFFFFF, KERN_DATA_FLAG, 0xCF),
UserCodeSegment(0, 0xFFFFFFFF, USER_CODE_FLAG, 0xCF),
UserStackSegment(0, 0xFFFFFFFF, USER_STACK_FLAG, 0xCF),
UserDataSegment(0, 0xFFFFFFFF, USER_DATA_FLAG, 0xCF)
{
	uint32_t gdtPtr[2];
	gdtPtr[1] = (uint32_t)this;
	gdtPtr[0] = sizeof(GlobalDescriptorTable) << 16;
	asm volatile("lgdt (%0)": :"p" (((uint8_t *) gdtPtr) + 2));
	asm volatile("movw $0x10, %ax;"
				"movw %ax, %ds;"
				"movw %ax, %es;"
				"movw %ax, %fs;"
				"movw %ax, %gs;"
				"movw %ax, %ss;"
				"ljmp $0x08, $bye;"
				"bye:"
				);
				mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter.
lidt [eax]        ; Load the IDT pointer.
ret
}

InterruptDescriptorTable::InterruptDescriptor::InterruptDescriptor(uint32_t base,
	 											uint16_t sel, uint8_t flags)
{
	base_lo = base & 0xFFFF;
	base_hi = (base >> 16) & 0xFFFF;

	this->sel = sel;
	always0 = 0;
	this->flags = flags;
}
