#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <avr/io.h>
#include <util/delay.h>

#define FULL_STEP 0
#define HALF_STEP 1


typedef struct Motor {
	uint8_t step_mode;
	uint8_t step;
	uint16_t step_delay;
	uint8_t steps[4][4];
	uint8_t halfsteps[8][4];
} Motor;

extern Motor motor1;
extern Motor motor2;

void delay_ms(uint16_t ms);

void m1_step(int16_t nbr_steps);
void m2_step(int16_t nbr_steps);


void m1_off();
void m2_off();

void m1_set_step_delay(int timeout);
void m2_set_step_delay(int timeout);


#endif