#include "serial.h"


CircularBuffer cb;

void uart_init() 
{
	cb_init(&cb);
	UBRR0H = ( MYUBRR >> 8 );
	UBRR0L = MYUBRR;
	UCSR0A |= ( 1 << U2X0 );
	UCSR0B |= (1 << RXEN0 ) | (1 << TXEN0 ) | ( 1 << RXCIE0 );
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
	sei();
	xdev_out(uart_putc);
}

void uart_putc(char c) 
{
 	while ( !( UCSR0A & ( 1 << UDRE0 ) ) );
		UDR0 = c;
}


ISR(USART_RX_vect) 
{
	char r = UDR0;
	cb_write(&cb, r);
} 
