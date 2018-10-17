#ifndef INTERRUPTS_MANAGER_H
#define INTERRUPTS_MANAGER_H

#include "types.h"
#include "GlobalDescriptorTable.h"
class InterruptsManager;

#define INTERRUPT_GATE			0x8E //1000 1110 first bit signify that the entry is present
#define IDT_MAX_ENTRIES			256
#define IDT_BASE				0x0
#define IDT_ENTRY_SIZE			8
#define IDT_SIZE				IDT_ENTRY_SIZE * IDT_MAX_ENTRIES - 1 // Don't overlap with GDT
#define TIMER_INT_NB			32

class	InterruptHandler
{
protected:
	uint8_t	interruptNb;
	InterruptsManager *interruptsManagerPtr;

// public:
	InterruptHandler(uint8_t interruptNb, InterruptsManager *interruptsManagerPtr);
	~InterruptHandler();
public:
	virtual uint32_t execInterruptRoutine(uint32_t esp);
};

class	InterruptsManager
{
private:
	static InterruptsManager *interruptsManagerPtr;
	void initPIC();

public:
	InterruptHandler *handlers[256];

	struct	InterruptDescriptor
	{
		uint16_t	base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
		uint16_t	sel;                 // Kernel segment selector.
		uint8_t		reserved;             // This must always be zero.
		uint8_t		flags;               // More flags. See documentation.
		uint16_t	base_hi;             // The upper 16 bits of the address to jump to.
	}__attribute__((packed));

	struct InterruptDescriptorTablePointer
	{
		uint16_t size;
		uint32_t base;
	} __attribute__((packed));

	static InterruptDescriptor interruptDescriptorTable[256];

	static void setIDTentry(uint8_t interruptNb, void (*handler)(), uint16_t sel, uint8_t flags);
	static void sendEndOfInterrupt(uint8_t interruptNb);

public:
	InterruptsManager(GlobalDescriptorTable *gdt);

	/*
	** Methods are static to avoid the implicit "this" pointer on the stack.
	** If the methods weren't the compiler would generate code to get
	** the last pushed parameter for a function at ebp + 12 (last ebp save + eip + "this" pointer)
	** instead of just ebp + 8 and we would forced to push a dummy "this" before the call.
	*/
	static uint32_t handleInterrupt(uint8_t interruptNb, uint32_t esp);

	/*
	** The handleInterrupt function will serve as an entryPoint for the asm code
	** the member function doHandleInterrupt will serve to return in our object oriented code
	** with the static pointer on InterruptsManager.
	*/
	uint32_t doHandleInterrupt(uint8_t interruptNb, uint32_t esp);
	static void ignoreInterruptRequest();

	static void handleInterruptRequest0x00();
	static void handleInterruptRequest0x01();
	static void handleInterruptRequest0x02();
	static void handleInterruptRequest0x03();
	static void handleInterruptRequest0x04();
	static void handleInterruptRequest0x05();
	static void handleInterruptRequest0x06();
	static void handleInterruptRequest0x07();
	static void handleInterruptRequest0x08();
	static void handleInterruptRequest0x09();
	static void handleInterruptRequest0x0A();
	static void handleInterruptRequest0x0B();
	static void handleInterruptRequest0x0C();
	static void handleInterruptRequest0x0D();
	static void handleInterruptRequest0x0E();
	static void handleInterruptRequest0x0F();
	// static void handleInterruptRequest0x80();

	static void handleException0x00();
	static void handleException0x01();
	static void handleException0x02();
	static void handleException0x03();
	static void handleException0x04();
	static void handleException0x05();
	static void handleException0x06();
	static void handleException0x07();
	static void handleException0x08();
	static void handleException0x09();
	static void handleException0x0A();
	static void handleException0x0B();
	static void handleException0x0C();
	static void handleException0x0D();
	static void handleException0x0E();
	static void handleException0x0F();
	static void handleException0x10();
	static void handleException0x11();
	static void handleException0x12();
	static void handleException0x13();

	void initIdt();
};

#endif
