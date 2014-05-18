#include "cb.h"

void cb_init(CircularBuffer *cb)
{
	cb->start = &(cb->buff[0]);
	cb->end = &(cb->buff[ CB_BUFF_SIZE - 1]);
	cb->read = &(cb->buff[0]);
	cb->write = &(cb->buff[0]);
}

void cb_write(CircularBuffer *cb, unsigned char data)
{
	*(cb->write) = data;
	if(cb->write == cb->end)
		cb->write = cb->start;
	else
		cb->write++;
	
}

uint8_t cb_read(CircularBuffer *cb, unsigned char *data)
{
	if(cb->read != cb->write) {
		*data = *(cb->read);
		if(cb->read != cb->end)
			cb->read++;
		else
			cb->read = cb->start;
		return 1;
	}
	return 0;
}
