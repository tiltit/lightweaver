#ifndef CB_H
#define CB_H

#include <stdint.h>

#define CB_BUFF_SIZE 80

typedef struct {
	char *start;
	char *end;
	char *read;
	char *write;
	char buff[ CB_BUFF_SIZE ];
	
} CircularBuffer;

void cb_init(CircularBuffer *cb);
uint8_t cb_read(CircularBuffer *cb, unsigned char *data);
void cb_write(CircularBuffer *cb, unsigned char data);


#endif
