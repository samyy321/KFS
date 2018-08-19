#include "GlobalDescriptorTable.h"
#include "lib.h"

GlobalDescriptorTable::GlobalDescriptorTable()
: nullSegment(0, 0, 0, 0),
KernCodeSegment(0, 0xFFFFFFFF, KERN_CODE_FLAG, PAGE_BLOCK),
KernStackSegment(0, 0xFFFFFFFF, KERN_DATA_FLAG, PAGE_BLOCK), // STACK FLAG causes crash on virtualbox
KernDataSegment(0, 0xFFFFFFFF, KERN_DATA_FLAG, PAGE_BLOCK),
UserCodeSegment(0, 0xFFFFFFFF, USER_CODE_FLAG, PAGE_BLOCK),
UserStackSegment(0, 0xFFFFFFFF, USER_DATA_FLAG, PAGE_BLOCK),
UserDataSegment(0, 0xFFFFFFFF, USER_DATA_FLAG, PAGE_BLOCK)
{
	GlobalDescriptorTablePointer gdtPtr;

	gdtPtr.size  = GDT_SIZE;
	gdtPtr.base = GDT_BASE;
	MemLib::memcpy((char *)gdtPtr.base, (char*)this, gdtPtr.size);

	asm("lgdt %0" : : "m" (gdtPtr));
	asm("movw $0x10, %ax;"
				"movw %ax, %ds;"
				"movw %ax, %es;"
				"movw %ax, %fs;"
				"movw %ax, %gs;"
				"movw %ax, %ss;"
				"ljmp $0x08, $offset;"
				"offset:"
				);
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base,
								uint32_t limit, uint8_t access, uint8_t gran)
{
	base_low = base & 0xFFFF;
	base_middle = (base >> 16) & 0xFF;
	base_high = (base >> 24) & 0xFF;

	limit_low = limit & 0xFFFF;
	granularity = (limit >> 16) & 0x0F;
	granularity |= gran & 0xF0;
	this->access = access;
}

uint16_t GlobalDescriptorTable::getKernCodeSegment()
{
	return (uint8_t*)&KernCodeSegment - (uint8_t*)this;
}
