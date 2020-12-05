/*
 *
 *  Created on: Nov 30, 2020
 *      Author: maitr
 */


/*
 */

#include <avr/io.h>
#include "uart.h"

#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>

#include <util/delay.h>

#include "Test_BNO055.h"
#include "bno055.h"
#include "i2c.h"
#include "stepper.h"
#include "ADC_READ.h"
/*************************************************************************************/


int main(void)
{
	//AVR_Init();
	UART_Init(115200);
	init_stepper();
	UART_Printf("Hello");

	//_delay_ms(750);
//
//
//	DDRC |= _BV(5);		//Makes PORTC, bit 5 as Output //sda
//	DDRC |= _BV(4);		//Makes PORTC, bit 4 as Output//scl
//
//	data = 0;
//	init_i2c();
//
//
//	start_wait_i2c(BNO055_ADDRESS+I2C_WRITE);	//Set device address and read mode
//	write_i2c(BNO055_OPR_MODE_ADDR);
//	write_i2c(OPERATION_MODE_NDOF);		//Set operation mode to IMU
//	stop_i2c();
//	_delay_ms(10);

  //  BNO_Calib();
  DDRD |= _BV(2);

	// OCR1A (port B, 1) as output
	DDRB |= _BV(1);
	TCCR1A |= 1 << WGM11 | 1 << COM1A1 | 1 << COM1A0; // Inverted mode
	TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS11; // prescaler is 8

	ICR1 = 39999;

	int pulse_width = 3000; // for 1.5 ms pulse width!

	OCR1A = ICR1 - pulse_width;
	//Endless Loop
	while(1)
	{

        stepper_loop();
     //   BNO_Euler_data();

		_delay_ms(500);
	}
}
