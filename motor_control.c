#include <stdlib.h>
#include "motor_control.h"

Motor motor1 = {
	HALF_STEP,
	0,
	5,
	{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	},
	{
		{1,0,0,0},
		{1,1,0,0},
		{0,1,0,0},
		{0,1,1,0},
		{0,0,1,0},
		{0,0,1,1},
		{0,0,0,1},
		{1,0,0,1}
	}
};

Motor motor2 = {
	HALF_STEP,
	0,
	5,
	{
		{1,0,0,0},
		{0,0,1,0},
		{0,1,0,0},
		{0,0,0,1}
	},
	{
		{1,0,0,0},
		{1,0,1,0},
		{0,0,1,0},
		{0,1,1,0},
		{0,1,0,0},
		{0,1,0,1},
		{0,0,0,1},
		{1,0,0,1}
	}
};

inline void delay_ms(uint16_t ms)
{
	while(ms>0) {
		ms--;
		_delay_ms(1);
	}
}

inline void delay_us(uint16_t us)
{
	while(us>0) {
		us--;
		_delay_us(1);
	}	
}

inline void m1_fullstep() {
	PORTC &= ~(0b00001111);
	PORTC |= (motor1.steps[motor1.step][0] << 0) 
		| (motor1.steps[motor1.step][1] << 1)
		| (motor1.steps[motor1.step][2] << 2)
		| (motor1.steps[motor1.step][3] << 3);
}

inline void m1_halfstep() {
	PORTC &= ~(0b00001111);
	PORTC |= (motor1.halfsteps[motor1.step][0] << 0) 
		| (motor1.halfsteps[motor1.step][1] << 1)
		| (motor1.halfsteps[motor1.step][2] << 2)
		| (motor1.halfsteps[motor1.step][3] << 3);
}

void m1_step(int16_t nbr_steps)
{
	uint16_t i = abs(nbr_steps);
	while(i-- != 0) {

		if(nbr_steps > 0)
			motor1.step++;
		else
			motor1.step--;

		switch(motor1.step_mode) {
			case FULL_STEP:
				motor1.step %= 4;
				m1_fullstep();
				break;
			case HALF_STEP:
				motor1.step %= 8;
				m1_halfstep();
			break;
		}
		delay_ms(motor1.step_delay);
	}
}

inline void m2_fullstep() 
{
	PORTD &= ~(0b11100000);
	PORTB &= ~(0b00000001);
	PORTD |= (motor2.steps[motor2.step][0] << 5) 
		| (motor2.steps[motor2.step][1] << 6)
		| (motor2.steps[motor2.step][2] << 7);
	PORTB |= (motor2.steps[motor2.step][3] << 0);
} 

inline void m2_halfstep() 
{
	PORTD &= ~(0b11100000);
	PORTB &= ~(0b00000001);
	PORTD |= (motor2.halfsteps[motor2.step][0] << 5) 
		| (motor2.halfsteps[motor2.step][1] << 6)
		| (motor2.halfsteps[motor2.step][2] << 7);
	PORTB |= (motor2.halfsteps[motor2.step][3] << 0);
} 

void m2_step(int16_t nbr_steps)
{	
	int i = abs(nbr_steps);
	while(i-- != 0) {
		
		if(nbr_steps > 0)
			motor2.step++;
		else if (nbr_steps < 0)
			motor2.step--;

		switch(motor2.step_mode) {
			case FULL_STEP:
				motor2.step %= 4;
				m2_fullstep();
			break;

			case HALF_STEP:
				motor2.step %= 8;
				m2_halfstep();
			break;
		}
		delay_ms(motor2.step_delay);
	}
}

void m1_off() {
	PORTC &= ~(0b00001111);
}

void m2_off() {
	PORTD &= ~(0b11100000);
	PORTB &= ~(0b00000001);
}

void m1_set_step_delay(int timeout)
{
	motor1.step_delay = timeout;
};

void m2_set_step_delay(int timeout)
{
	motor2.step_delay = timeout;
};

/*
void line(int x2, int y2)
{
	int x1 = 0;
	int y1 = 0;
  int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;

  dx=x2-x1;      //the horizontal distance of the line 
  dy=y2-y1;      // the vertical distance of the line
  dxabs=abs(dx);
  dyabs=abs(dy);
  sdx=sgn(dx);
  sdy=sgn(dy);
  x=dyabs>>1;
  y=dxabs>>1;
  px=x1;
  py=y1;

  //VGA[(py<<8)+(py<<6)+px]=color;

  if (dxabs>=dyabs) //the line is more horizontal than vertical
  {
    for(i=0;i<dxabs;i++)
    {
      y+=dyabs;
      if (y>=dxabs)
      {
        y-=dxabs;
        py+=sdy;
      }
      px+=sdx;
      //put_pixel(px,py,color);
    }
  }
  else // the line is more vertical than horizontal 
  {
    for(i=0;i<dyabs;i++)
    {
      x+=dxabs;
      if (x>=dyabs)
      {
        x-=dyabs;
        px+=sdx;
      }
      py+=sdy;
      //put_pixel(px,py,color);
    }
  }
}

*/