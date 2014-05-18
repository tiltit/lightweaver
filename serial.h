#ifndef SERIAL_H
#define SERIAL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "cb.h"

#include "lib/xprintf.h"

#define BAUD 115200
#define MYUBRR ( ( F_CPU / ( BAUD * 8UL ) ) - 1 )

extern CircularBuffer cb;

void uart_init();
void uart_putc(char c);

#endif