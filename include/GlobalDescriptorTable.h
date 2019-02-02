#ifndef GDT_H
#define GDT_H

#include "types.h"

/*
 * The access flags byte:
 * bit 7: Is segment present? (1 = Yes).
 * bits 6 and 5: Descriptor privilege level - Ring 0 - 3.
 * bit 4: 0 if it is a system descriptor, 1 if it is code data or stack
 * bit 3: Executable bit. If 1 code in this segment can be executed, ie. a code descriptor. If 0 it is a data descriptor.
 * bit 2: Direction bit for data descriptors/Conforming bit for code descriptors.
 * bit 1: Readable bit/Writable bit.
 * Readable bit for code descriptors: Whether read access for this segment is allowed. Write access is never allowed for code segments.
 * Writable bit for data descriptors: Whether write access for this segment is allowed. Read access is always allowed for data segments.
 * bit 0: Accessed bit. Just set to 0. The CPU sets this to 1 when the segment is accessed.
 * source: https://wiki.osdev.org/Global_Descriptor_Table
 */
#define KERN_CODE_FLAG	0x9A // 1001 1010
#define KERN_DATA_FLAG	0x92 // 1001 0010
#define KERN_STACK_FLAG	0x96 // 1001 0110 We set the bit 2 to have a growing down stack segment
#define USER_CODE_FLAG	0xFA // 1111 1010
#define USER_DATA_FLAG	0xF2 // 1111 0010
#define USER_STACK_FLAG	0xF6 // 1111 0110

/* Granularity byte:
 * bit 7:  Granularity bit. If 0 the limit is in 1 B blocks (byte granularity), if 1 the limit is in 4 KiB blocks (page granularity).
 * bit 6: Size bit. If 0 the selector defines 16 bit protected mode. If 1 it defines 32 bit protected mode. You can have both 16 bit and 32 bit selectors at once.
 */
#define BYTE_BLOCK 0x40 // 0100 0000
#define PAGE_BLOCK 0xC0 // 1100 0000

#define GDT_BASE		0x00000800
#define GDT_NB_ENTRIES	7
#define	GDT_ENTRY_SIZE	sizeof(SegmentDescriptor)
#define GDT_SIZE 		GDT_ENTRY_SIZE * GDT_NB_ENTRIES

class	GlobalDescriptorTable
{
public:
	class	SegmentDescriptor
	{
	private:
		uint16_t	limit_low;
		uint16_t	base_low;
		uint8_t		base_middle;
		uint8_t		access;		// Access flags, determine what ring this segment can be used in.
		uint8_t		granularity;
		uint8_t		base_high;
	public:
		SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
	}__attribute__((packed));

	struct GlobalDescriptorTablePointer
	{
		uint16_t size;
		uint32_t base;
	} __attribute__((packed));

private:
	SegmentDescriptor	nullSegment;
	SegmentDescriptor	KernCodeSegment;
	SegmentDescriptor	KernStackSegment;
	SegmentDescriptor	KernDataSegment;
	SegmentDescriptor	UserCodeSegment;
	SegmentDescriptor	UserStackSegment;
	SegmentDescriptor	UserDataSegment;

public:
	GlobalDescriptorTable();
	uint16_t getKernCodeSegment();
};

#endif
