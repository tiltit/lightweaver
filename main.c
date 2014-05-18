#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include "cb.h"
#include "motor_control.h"
#include "serial.h"
#include "serial_commands.h"

void setup_io(void) {
	/* ** Motor 1 ** */
	DDRC |= _BV(0) | _BV(1) | _BV(2) | _BV(3);

	/* ** Motor 2 ** */
	DDRD |=  _BV(5) | _BV(6) | _BV(7);
	DDRB |= _BV(0);

	// LEDS
	DDRB |= _BV(1) | _BV(2) | _BV(3);
	PORTB &= ~(_BV(1) | _BV(2) | _BV(3));
	// PB1 Green
	// PB2 Red
	// PB3 Blue

	// Camera shutter PB5
	DDRB |= _BV(5);
	PORTB &= ~_BV(5);

}

void setup_pwm()
{
	// PWM 1
	TCCR1B |= (1<<CS11) | (1<<CS10);
	TCCR1A |= (1<<WGM10)| (1<<WGM12);

	TCCR1A |= (1<<COM1A1);
	TCCR1A |= (1<<COM1B1);
	OCR1A = 0;
	OCR1B = 0;

	// PWM 2
	TCCR2B |= (1<<CS22);
	TCCR2A |= (1<<WGM20);
	TCCR2A |= (1<<COM2A1);
	OCR2A = 0;
}

void set_led_color(uint8_t r, uint8_t g, uint8_t b)
{
	OCR1B = r;
	OCR1A = g;
	OCR2A = b;
}

void process_packet(uint8_t *packet, uint8_t packet_length)
{
	uint8_t step_delay;
	int nSteps = 0;
	switch(packet[0]) {
		case CMD_MOTOR1:
			step_delay = packet[1];
			nSteps = (int16_t)((packet[2] << 8) | packet[3]);
			//xprintf("M1 :%d\n", nSteps);
			m1_set_step_delay(step_delay);
			m1_step(nSteps);
			break;

		case CMD_MOTOR2:
			step_delay = packet[1];
			nSteps = (int16_t)((packet[2] << 8) | (packet[3]));
			//xprintf("M2 :%d\n", nSteps);
			m2_set_step_delay(step_delay);
			m2_step(nSteps);
			break;

		case CMD_LED_COLOR:
			set_led_color(packet[1],packet[2],packet[3]);
			break;
		case CMD_RELEASE_MOTOR1:
			m1_off();
			break;
		case CMD_RELEASE_MOTOR2:
			m2_off();
			break;
		case CMD_SHUTTER_OPEN:
			PORTB |= _BV(5);
			break;
		case CMD_SHUTTER_CLOSE:
			PORTB &= ~_BV(5);
			break;


		default:
			xprintf("Command Error\n");
			break;
	}
}

int main() 
{
	uint8_t bytes_received = 0;
	uint8_t zero_count = 0;
	bool receiving_cmd = false;
	uint8_t packet_length;

	uint8_t packet[20];
	uint8_t packet_index = 0;

	uart_init();
	setup_io();
	m1_off();
	m2_off();
	setup_pwm();
	set_led_color(255,255,255);
	int i;
	xprintf("hello\n");

	uint8_t data;

	while ( 1 ) {
		while(cb_read(&cb, &data)) {
			
			bytes_received++;

			if((receiving_cmd==false) && (data==0)) {
				zero_count++;
			}

			if( (receiving_cmd == false) && (data!=0) && (zero_count>=5) ) {
				packet_length = data;
				receiving_cmd = true;
				break;
			}

			if(receiving_cmd == true) {

				packet[packet_index++] = data;
				if(packet_index == packet_length) {
					// Packet received
					process_packet(packet, packet_length);
					xprintf("_BP %d\n", bytes_received);
					bytes_received = 0;
					zero_count = 0;
					receiving_cmd = false;
					packet_index = 0;
					
				}
			}
		}
   	}
} 


