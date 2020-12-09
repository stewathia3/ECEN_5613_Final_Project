/*
 *
 *
 *     Author: Sanjana Tewathia
 *  Find definitions for the functions in servo.h file
 */

#include <avr/io.h>
#include "uart.h"
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>
#include "ADC_READ.h"
#include <util/delay.h>
#include "Test_BNO055.h"
#include "bno055.h"
#include "i2c.h"
#include "servo.h"

int pulse_width;
void servo_init()
{
	// Initialize Servo PWM GPIO pin as output
	DDRD |= _BV(2);
	// OCR1A (port B, 1) as output
	DDRB |= _BV(1);
	DDRB |= _BV(2);
	TCCR1A |= 1 << WGM11 | 1 << COM1A1 | 1 << COM1A0 | 1 << COM1B1 | 1 << COM1B0;	// Inverted mode
	TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS11;	// prescaler is 8
	ICR1 = 39999;
	pulse_width = 3000;	// for 1.5 ms pulse width!
	OCR1A = ICR1 - pulse_width; //update to get 1.5 pulse width on pin OC1A

}

void servo_left()
{
	pulse_width += 200; //change pulse width to obtain 200ms change
	if (pulse_width > 4000) {} //if threshold is reached do nothing dont move further left
	else
	{
		BNO_Euler_data(); // get IMu data
		OCR1A = ICR1 - pulse_width; //get required pulse width // tilt stepper
		_delay_ms(100);
	}
}

void servo_right()
{
	pulse_width -= 200; // reduce pulse width to tilt servo in another direction
	if (pulse_width < 2200) {}//if threshold is reached do nothing dont move further right
	else
	{
		BNO_Euler_data(); // get IMu data
		OCR1A = ICR1 - pulse_width;//get required pulse width // tilt stepper
	}
}
