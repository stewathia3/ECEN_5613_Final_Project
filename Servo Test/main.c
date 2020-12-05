#include <avr/io.h>
#include "uart.h"

#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>

#include "util/delay.h"


int main(void) {

	// Initialize Servo PWM GPIO pin as output
	DDRD |= _BV(2);

	// OCR1A (port B, 1) as output
	DDRB |= _BV(1);
	TCCR1A |= 1 << WGM11 | 1 << COM1A1 | 1 << COM1A0; // Inverted mode
	TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS11; // prescaler is 8

	ICR1 = 39999;

	int pulse_width = 3000; // for 1.5 ms pulse width!

	OCR1A = ICR1 - pulse_width;

	// Move servo to 1.6 ms position

	while(1) {

	}
}
