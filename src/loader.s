%define MAGIC		0x1BADB002
%define FLAGS		0x00
%define CHECKSUM	-(MAGIC + FLAGS)

section .text
	align	4
	dd		MAGIC
	dd		FLAGS
	dd		CHECKSUM

global loader
extern kmain

loader:
	mov		esp, $kernel_stack
	call	kmain

stop:
	hlt

section .bss

resb		8192
kernel_stack:
