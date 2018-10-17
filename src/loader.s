%define MAGIC		0x1BADB002
%define FLAGS		0x00
%define CHECKSUM	-(MAGIC + FLAGS)

section .multiboot
align	4
dd		MAGIC
dd		FLAGS
dd		CHECKSUM

section .text

global loader
extern kmain

loader:
	mov		esp, $kernel_stack
	call	kmain

stop:
	hlt

section .bss

resb		2*1024*1024
kernel_stack:
