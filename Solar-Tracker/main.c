/*
 *
 *
 *     Author: maitreyee Rao
 */

#include <avr/io.h>
#include "uart.h"
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>
#include "servo.h"
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
	servo_init();
	UART_Printf("Hello");

	_delay_ms(750);

	DDRC |= _BV(5);	//Makes PORTC, bit 5 as Output	//sda
	DDRC |= _BV(4);	//Makes PORTC, bit 4 as Output//scl

	data = 0;
	init_i2c();

	start_wait_i2c(BNO055_ADDRESS + I2C_WRITE);	//Set device address and read mode
	write_i2c(BNO055_OPR_MODE_ADDR);
	write_i2c(OPERATION_MODE_NDOF);	//Set operation mode to IMU
	stop_i2c();
	_delay_ms(10);

	BNO_Calib(); //calibrate IMU
	while (1)
	{
		quadphoto_predict(); //enter SUN TRACKING MODE
		_delay_ms(1000);
	}
}
