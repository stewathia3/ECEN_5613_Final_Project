/*
 * Maitreyee Rao
 * ECEN 5613 - Fall 2020 - Prof. McClure
 * University of Colorado Boulder
 * Revised 12/6/20
 *
 * Find definitions for the functions in ADC_READ.h file
 *
 */

#include <avr/io.h>
#include "uart.h"
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>
#include "ADC_READ.h"
#include <util/delay.h>
#include "servo.h"
#include "base_servo.h"
/************************************************************************************/
#define THRESHOLD 800
/*************************************************************************************/

int ADC_READ(uint8_t adcpin)
{
	int ADC_value; //integer to store adc value

	ADMUX = adcpin; //mux the required adc pin
	ADMUX |= (1 << REFS0);	// use AVref as the reference
	ADMUX &= ~(1 << ADLAR);	// clear for 10 bit

	// 128 prescale for 8Mhz
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	ADCSRA |= (1 << ADEN);	// Enable the ADC
	ADCSRA |= (1 << ADSC);	// Start the ADC conversion

	while (ADCSRA &(1 << ADSC));	// waits for the ADC to finish

	ADC_value = ADCL;
	ADC_value = (ADCH << 8) + ADC_value;	// ADCH is read so ADC can be updated again

	return ADC_value;
}

void quadphoto_predict()
{
	int ADCvalue0; //storing value of 2nd quadrant attached to ADC0
	int ADCvalue1; //storing value of 1nd quadrant attached to ADC1
	int ADCvalue2; //storing value of 4th quadrant attached to ADC2
	int ADCvalue3; //storing value of 3rd quadrant attached to ADC3
	int min_value;  //store minimum value of two quadrants
	int min_value1;//store min of 4 quadrants
	ADCvalue1 = ADC_READ(0); //read adc values
	ADCvalue0 = ADC_READ(1);
	ADCvalue3 = ADC_READ(2);
	ADCvalue2 = ADC_READ(3);
    //calculate min of the obtained 4 quadrant values
	min_value1 = MIN_FOUR(ADCvalue0, ADCvalue1, ADCvalue2, ADCvalue3);

	if (min_value1 < THRESHOLD) // check if the value is below threshold, meaning some light source is detected
	{
		if (min_value1 == ADCvalue0) //if the2nd quadrant is giving minimum value check adjacent quadrants
		{
			min_value = MIN(ADCvalue1, ADCvalue3); //take min of adjacent quadrants
			if ((ADCvalue1 == 0) && (ADCvalue2 == 0) && (ADCvalue3 == 0)) {} //if all are zero do nothing
			else if (min_value == ADCvalue1)//if quad 1 is min
			{
				UART_Printf("\n\rADC");
				UART_Printf(" %d", ADCvalue0);
				UART_Printf(" %d", ADCvalue1);
				UART_Printf(" %d", ADCvalue2);
				UART_Printf(" %d", ADCvalue3);
				servo_right(); //rotate servo to right

			}
			else if (min_value == ADCvalue3) //if quad 3 is min
			{
				UART_Printf("\n\rADC");
				UART_Printf(" %d", ADCvalue0);
				UART_Printf(" %d", ADCvalue1);
				UART_Printf(" %d", ADCvalue2);
				UART_Printf(" %d", ADCvalue3);

				base_servo_left(); //rotate base servo to left

			}
		}
		else if (min_value1 == ADCvalue1) //if the 1st quadrant is giving minimum value check adjacent quadrants
		{
			min_value = MIN(ADCvalue0, ADCvalue2); //take minimum of 2nd and 4th
			if ((ADCvalue0 == 0) && (ADCvalue2 == 0) && (ADCvalue3 == 0)) {} //if all are 0 light source found
			else if (min_value == ADCvalue0)//if 2nd is min turn servo to right
			{
				UART_Printf("\n\rADC");
				UART_Printf(" %d", ADCvalue0);
				UART_Printf(" %d", ADCvalue1);
				UART_Printf(" %d", ADCvalue2);
				UART_Printf(" %d", ADCvalue3);

				servo_right();

			}
			else if (min_value == ADCvalue2) // if 4th is minimum turn base servo to right
			{
				UART_Printf("\n\rADC");
				UART_Printf(" %d", ADCvalue0);
				UART_Printf(" %d", ADCvalue1);
				UART_Printf(" %d", ADCvalue2);
				UART_Printf(" %d", ADCvalue3);

				base_servo_right();

			}
		}
		else if (min_value1 == ADCvalue2)//if minimum is 4th quadrant check adjacent quadrants
		{
			min_value = MIN(ADCvalue1, ADCvalue3); //take minimum of 3rd and 1st quadrant
			if ((ADCvalue0 == 0) && (ADCvalue1 == 0) && (ADCvalue3 == 0)) {}
			else if (min_value == ADCvalue3)//if 4th and 3rd are minimum tilt servo to right
			{
				UART_Printf("\n\rADC");
				UART_Printf(" %d", ADCvalue0);
				UART_Printf(" %d", ADCvalue1);
				UART_Printf(" %d", ADCvalue2);
				UART_Printf(" %d", ADCvalue3);

				servo_right();

			}
			else if (min_value == ADCvalue0)//if 4th and 1sr are minimum tilt base servo to right
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
		else if (min_value1 == ADCvalue3)//if 3rd quadrant is minimum
		{
			min_value = MIN(ADCvalue2, ADCvalue0); //take min of 2nd and 4th
			if ((ADCvalue1 == 0) && (ADCvalue2 == 0) && (ADCvalue0 == 0)) {}
			else if (min_value == ADCvalue2) // if 3rd and 4th are min tilt servo to left
			{
				UART_Printf("\n\rADC");
				UART_Printf(" %d", ADCvalue0);
				UART_Printf(" %d", ADCvalue1);
				UART_Printf(" %d", ADCvalue2);
				UART_Printf(" %d", ADCvalue3);
				servo_left();

			}
			else if (min_value == ADCvalue0) //if 3rd quadrant and 2nd quadrant are minimum move servo to left
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
	else {}
}
