#include <avr/io.h>
#include "uart.h"
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>
#include "ADC_READ.h"
#include <util/delay.h>
//#include "Test_BNO055.h"
//#include "bno055.h"
//#include "i2c.h"
#include "servo.h"
#include "base_servo.h"

/*************************************************************************************/



int ADC_READ(uint8_t adcpin)
{
	int ADC_value;

	ADMUX = adcpin;
	ADMUX |= (1 << REFS0);	// use AVcc as the reference
	ADMUX &= ~(1 << ADLAR);	// clear for 10 bit resolution

	// 128 prescale for 8Mhz
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	ADCSRA |= (1 << ADEN);	// Enable the ADC
	ADCSRA |= (1 << ADSC);	// Start the ADC conversion

	while (ADCSRA &(1 << ADSC));	// waits for the ADC to finish

	ADC_value = ADCL;
	ADC_value = (ADCH << 8) + ADC_value;	// ADCH is read so ADC can be updated again

	return ADC_value;
}

void sunsensor_predict()
{
	int ADCvalue0;
	int ADCvalue1;
	int ADCvalue2;
	int ADCvalue3;
	int min_value;
	int min_value1;
	ADCvalue1 = ADC_READ(0);
	ADCvalue0 = ADC_READ(1);
	ADCvalue3 = ADC_READ(2);
	ADCvalue2 = ADC_READ(3);	//for pcb




	min_value1 = MIN_FOUR(ADCvalue0, ADCvalue1, ADCvalue2, ADCvalue3);
	if (min_value1 < 800)
	{
		if (min_value1 == ADCvalue0)
		{
			min_value = MIN(ADCvalue1, ADCvalue3);
			if ((ADCvalue1 == 0) && (ADCvalue2 == 0) && (ADCvalue3 == 0))
			{

			}
			else if (min_value == ADCvalue1)
			{
                    UART_Printf("\n\rADC");
                    UART_Printf(" %d", ADCvalue0);
                    UART_Printf(" %d", ADCvalue1);
                    UART_Printf(" %d", ADCvalue2);
                    UART_Printf(" %d", ADCvalue3);
                    servo_right();



			}
			else if (min_value == ADCvalue3)
			{
                UART_Printf("\n\rADC");
                UART_Printf(" %d", ADCvalue0);
                UART_Printf(" %d", ADCvalue1);
                UART_Printf(" %d", ADCvalue2);
                UART_Printf(" %d", ADCvalue3);

			    base_servo_left();

			}
		}
		else if (min_value1 == ADCvalue1)
		{
			min_value = MIN(ADCvalue0, ADCvalue2);
			if ((ADCvalue0 == 0) && (ADCvalue2 == 0) && (ADCvalue3 == 0))
			{

			}
			else if (min_value == ADCvalue0)
			{
                UART_Printf("\n\rADC");
                UART_Printf(" %d", ADCvalue0);
                UART_Printf(" %d", ADCvalue1);
                UART_Printf(" %d", ADCvalue2);
                UART_Printf(" %d", ADCvalue3);

                servo_right();

			}
			else if (min_value == ADCvalue3)
			{
                UART_Printf("\n\rADC");
                UART_Printf(" %d", ADCvalue0);
                UART_Printf(" %d", ADCvalue1);
                UART_Printf(" %d", ADCvalue2);
                UART_Printf(" %d", ADCvalue3);
			   // BNO_Euler_data();
                base_servo_right();

			}
		}
		else if (min_value1 == ADCvalue2)
		{
			min_value = MIN(ADCvalue1, ADCvalue3);
			if ((ADCvalue0 == 0) && (ADCvalue1 == 0) && (ADCvalue3 == 0))
			{

			}
			else if (min_value == ADCvalue3)
			{
                UART_Printf("\n\rADC");
                UART_Printf(" %d", ADCvalue0);
                UART_Printf(" %d", ADCvalue1);
                UART_Printf(" %d", ADCvalue2);
                UART_Printf(" %d", ADCvalue3);

				servo_left();


			}
			else if (min_value == ADCvalue1)
			{
                UART_Printf("\n\rADC");
                UART_Printf(" %d", ADCvalue0);
                UART_Printf(" %d", ADCvalue1);
                UART_Printf(" %d", ADCvalue2);
                UART_Printf(" %d", ADCvalue3);
			    //BNO_Euler_data();
			    base_servo_right();

			}
		}
		else if (min_value1 == ADCvalue3)
		{
			min_value = MIN(ADCvalue2, ADCvalue0);
			if ((ADCvalue1 == 0) && (ADCvalue2 == 0) && (ADCvalue0 == 0))
			{

			}
			else if (min_value == ADCvalue2)
			{
                UART_Printf("\n\rADC");
                UART_Printf(" %d", ADCvalue0);
                UART_Printf(" %d", ADCvalue1);
                UART_Printf(" %d", ADCvalue2);
                UART_Printf(" %d", ADCvalue3);
				servo_left();

			}
			else if (min_value == ADCvalue0)
			{
                UART_Printf("\n\rADC");
                UART_Printf(" %d", ADCvalue0);
                UART_Printf(" %d", ADCvalue1);
                UART_Printf(" %d", ADCvalue2);
                UART_Printf(" %d", ADCvalue3);

                base_servo_left();

			}
		}
	}
	else
	{

	}
}
