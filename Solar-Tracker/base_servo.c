/*
 *
 *
 *     Author: maitreyee Rao
 *  Find definitions for the functions in base_servo.h file
 */

#include "base_servo.h"

int j = 0;	// Keep track of base servo turning right 90 degrees
int k = 0;	// Keep track of base servo turning right 90 degrees
void base_servo_left()
{
	ICR1 = 39999;
	// CW PW
	if (k < 2)
	{
		// not yet reached 90 degrees to the left

		BNO_Euler_data();
		int pulse_width = 2900;
		OCR1B = ICR1 - pulse_width;
		_delay_ms(1625);
		// stop PW is 2925
		pulse_width = 2925;	// for 1.5 ms pulse width!
		OCR1B = ICR1 - pulse_width;
		j--;	// decrement j since we can move right
		k++;	// increment k for next time fcn is called
	}
}

void base_servo_right()
{
	// CCW PW
	if (j < 2)
	{
		BNO_Euler_data();
		int pulse_width = 2950;	// for 1.5 ms pulse width!
		OCR1B = ICR1 - pulse_width;
		_delay_ms(1625);
		// stop PW is 2925
		pulse_width = 2925;	// for 1.5 ms pulse width!
		OCR1B = ICR1 - pulse_width;
		k--;	// decrement k since we can move left
		j++;	// increment j for next time fcn is called
	}
}
