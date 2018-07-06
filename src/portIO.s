section .text

global readPort
global writePort

readPort:
	mov edx, [esp + 4]
	in al, dx
	ret

writePort:
	mov   edx, [esp + 4]
	mov   al, [esp + 4 + 4]
	out   dx, al
	ret
