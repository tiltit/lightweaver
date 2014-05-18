#ifndef SERIAL_H

#define SERIAL_H

#include <stdint.h>
#include <stdbool.h>


class Serial {

public:
	Serial();
	int init(const char *device);
	int uartClose();
	int uartRead(uint8_t *s);
	int uartWrite(uint8_t *s, uint8_t size);
	bool isOpen() const { return deviceStatus; };

private:
	int tty_fd;
	bool deviceStatus;

};

#endif