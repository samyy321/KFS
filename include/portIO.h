#ifndef PORTIO_H
#define PORTIO_H

extern "C" char readPort(unsigned short port);
extern "C" void writePort(unsigned short port, unsigned char data);

#endif
