#include "InterruptsManager.h"
#include "portIO.h"
#include "VgaBuffer.h"
#include "lib.h"

InterruptsManager::InterruptDescriptor InterruptsManager::interruptDescriptorTable[256];
InterruptsManager *InterruptsManager::interruptsManagerPtr = 0;

InterruptHandler::InterruptHandler(uint8_t interruptNb, InterruptsManager *interruptsManagerPtr)
{
	this->interruptNb = interruptNb;
	this->interruptsManagerPtr = interruptsManagerPtr;
	interruptsManagerPtr->handlers[interruptNb] = this;
}

InterruptHandler::~InterruptHandler()
{
	if (interruptsManagerPtr->handlers[interruptNb] == this)
		interruptsManagerPtr->handlers[interruptNb] = 0;
}

uint32_t InterruptHandler::execInterruptRoutine(uint32_t esp)
{
	return esp;
}

void InterruptsManager::setIDTentry(uint8_t interruptNb, void (*handler)(), uint16_t sel, uint8_t flags)
{
	interruptDescriptorTable[interruptNb].base_lo = (uint32_t)handler & 0xFFFF;
	interruptDescriptorTable[interruptNb].base_hi = ((uint32_t)handler >> 16) & 0xFFFF;

	interruptDescriptorTable[interruptNb].sel = sel;
	interruptDescriptorTable[interruptNb].reserved = 0;
	interruptDescriptorTable[interruptNb].flags = flags;
}

void InterruptsManager::initPIC()
{
	/*     			Ports
	*	 	 	PIC1	PIC2
	*	Command 0x20	0xA0
	*	Data	 0x21	0xA1
	*/

	/* ICW1 - begin initialization */
	writePort(0x20 , 0x11);
	writePort(0xA0 , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	writePort(0x21 , 0x20);
	writePort(0xA1 , 0x28);

	/* ICW3 - setup cascading */
	writePort(0x21 , 0x04);
	writePort(0xA1 , 0x02);

	/* ICW4 - environment info */
	writePort(0x21 , 0x01);
	writePort(0xA1 , 0x01);
	/* Initialization finished */

	/* mask interrupts */
	writePort(0x21 , 0x0);
	writePort(0xA1 , 0x0);
}

InterruptsManager::InterruptsManager(GlobalDescriptorTable *gdt)
{
	uint16_t KernCodeSegment = gdt->getKernCodeSegment();

	for (int i = 0; i < 256; i++)
	{
		setIDTentry(i, &ignoreInterruptRequest, KernCodeSegment, INTERRUPT_GATE);
		interruptsManagerPtr->handlers[i] = 0;
	}
	setIDTentry(0, &handleException0x00, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(1, &handleException0x01, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(2, &handleException0x02, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(3, &handleException0x03, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(4, &handleException0x04, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(5, &handleException0x05, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(6, &handleException0x06, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(7, &handleException0x07, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(8, &handleException0x08, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(9, &handleException0x09, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(10, &handleException0x0A, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(11, &handleException0x0B, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(12, &handleException0x0C, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(13, &handleException0x0D, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(14, &handleException0x0E, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(15, &handleException0x0F, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(16, &handleException0x10, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(17, &handleException0x11, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(18, &handleException0x12, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(19, &handleException0x13, KernCodeSegment, INTERRUPT_GATE);
	//
	setIDTentry(32, &handleInterruptRequest0x00, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(33, &handleInterruptRequest0x01, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(34, &handleInterruptRequest0x02, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(35, &handleInterruptRequest0x03, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(36, &handleInterruptRequest0x04, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(37, &handleInterruptRequest0x05, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(38, &handleInterruptRequest0x06, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(39, &handleInterruptRequest0x07, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(40, &handleInterruptRequest0x08, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(41, &handleInterruptRequest0x09, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(42, &handleInterruptRequest0x0A, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(43, &handleInterruptRequest0x0B, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(44, &handleInterruptRequest0x0C, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(45, &handleInterruptRequest0x0D, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(46, &handleInterruptRequest0x0E, KernCodeSegment, INTERRUPT_GATE);
	setIDTentry(47, &handleInterruptRequest0x0F, KernCodeSegment, INTERRUPT_GATE);

	InterruptDescriptorTablePointer idtPtr;
	idtPtr.size  = IDT_SIZE;
	idtPtr.base = IDT_BASE;
	MemLib::memcpy((char *)idtPtr.base, (char*)interruptDescriptorTable, idtPtr.size);

	asm("lidt %0" : : "m" (idtPtr));
}

void InterruptsManager::initIdt(void)
{
	interruptsManagerPtr = this;
	initPIC();
	asm("sti");
}

void InterruptsManager::sendEndOfInterrupt(uint8_t interruptNb)
{
	if (interruptNb >= 40)
		// Send reset signal to slave.
		writePort(0xA0 , 0x20);

	// Send reset signal to master. (As well as slave, if necessary).
	writePort(0x20, 0x20);
}

uint32_t InterruptsManager::doHandleInterrupt(uint8_t interruptNb, uint32_t esp)
{
	if (interruptNb > 0x20 && interruptNb < 0x30)
	{
		if (interruptsManagerPtr->handlers[interruptNb] != 0)
			esp = interruptsManagerPtr->handlers[interruptNb]->execInterruptRoutine(esp);
	}

	sendEndOfInterrupt(interruptNb);

	return esp;
}

uint32_t InterruptsManager::handleInterrupt(uint8_t interruptNb, uint32_t esp)
{
	if (interruptsManagerPtr != 0)
		return interruptsManagerPtr->doHandleInterrupt(interruptNb, esp);
	return esp;
}
