/*
 *
 *
 *      Author: maitreyee Rao
 */


/*
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


	while(1)
	{

     sunsensor_predict();
     _delay_ms(1000);
	}
}
