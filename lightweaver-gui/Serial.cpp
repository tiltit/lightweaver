#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "Serial.h"

using namespace std;

Serial::Serial() {
	deviceStatus = false;
}

int Serial::init(const char *device)
{
	struct termios tio;

	memset(&tio,0,sizeof(tio));
	tio.c_iflag=0;
	tio.c_oflag=0;
	// 8n1, see termios.h for more information
	tio.c_cflag=CS8|CREAD|CLOCAL;
	tio.c_lflag=0;
	tio.c_cc[VMIN]=1;
	tio.c_cc[VTIME]=5;

	tty_fd=open(device, O_RDWR | O_NONBLOCK);

	if(tty_fd < 0) {
		return tty_fd;
	}

	// 115200 baud
	cfsetospeed(&tio,B115200);            
	cfsetispeed(&tio,B115200);

	tcsetattr(tty_fd,TCSANOW,&tio);
	deviceStatus = true;
	return 0;
}

int Serial::uartClose() {
	close(tty_fd);
	deviceStatus = false;
	return 0;
}

int Serial::uartRead(uint8_t *s)
{
	unsigned char c;
	int count = 0;
	while (read(tty_fd,&c,1)>0) {
		s[count] = c;
		count++;
	}
	return count;
}

int Serial::uartWrite(uint8_t *s, uint8_t size)
{
	return write(tty_fd,s,size);
}