

#include <avr/io.h>
#include "uart.h"

#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>
#include "ADC_READ.h"
#include "math.h"
#include <util/delay.h>
int pulse_width;
/*************************************************************************************/

void servo_init()
{
    // Initialize Servo PWM GPIO pin as output
	DDRD |= _BV(2);
	// OCR1A (port B, 1) as output
	DDRB |= _BV(1);
	TCCR1A |= 1 << WGM11 | 1 << COM1A1 | 1 << COM1A0; // Inverted mode
	TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS11; // prescaler is 8
	ICR1 = 39999;
    pulse_width = 3000; // for 1.5 ms pulse width!
	OCR1A = ICR1 - pulse_width;


}
int ADC_READ(uint8_t adcpin)
{
    int ADC_value;

    ADMUX = adcpin;
    ADMUX |= (1 << REFS0);   // use AVcc as the reference
    ADMUX &= ~(1 << ADLAR);  // clear for 10 bit resolution

    // 128 prescale for 8Mhz
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    ADCSRA |= (1 << ADEN);    // Enable the ADC
    ADCSRA |= (1 << ADSC);    // Start the ADC conversion

    while(ADCSRA & (1 << ADSC)); // waits for the ADC to finish

    ADC_value = ADCL;
    ADC_value = (ADCH << 8) + ADC_value; // ADCH is read so ADC can be updated again

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
         ADCvalue2 = ADC_READ(3); //for pcb

         UART_Printf("\n\rADC0: %d",ADCvalue0);
        UART_Printf("\n\rADC1: %d",ADCvalue1);

         UART_Printf("\n\rADC2: %d",ADCvalue2);
         UART_Printf("\n\rADC3: %d",ADCvalue3);

         UART_Printf("\n\r*************************************************************\n\r");

    min_value1=MIN_FOUR(ADCvalue0,ADCvalue1,ADCvalue2,ADCvalue3);
    if (min_value1<400)
    {
    if(min_value1==ADCvalue0)
    {
        min_value= MIN(ADCvalue1,ADCvalue3);
        if((ADCvalue1==0)&&(ADCvalue2==0)&&(ADCvalue3==0))
        {
            UART_Printf("\n\rLIGHT HAS BEEN FOUND\n\r");
        }
        else if(min_value == ADCvalue1)
        {

            pulse_width -=200;
            if(pulse_width <2200)
            {
                UART_Printf("\n\r Do nothing");
            }
            else
            {
                OCR1A = ICR1 - pulse_width;
            }
            UART_Printf("\n\r servo right\n\r");
        }
        else if (min_value == ADCvalue3)
        {

            UART_Printf("\n\r stepper right\n\r");
        }

    }
    else if(min_value1==ADCvalue1)
    {
        min_value= MIN(ADCvalue0,ADCvalue2);
        if((ADCvalue0==0)&&(ADCvalue2==0)&&(ADCvalue3==0))
        {
            UART_Printf("\n\rLIGHT HAS BEEN FOUND\n\r");
        }
        else if(min_value == ADCvalue0)
        {

            pulse_width -=200;
            if(pulse_width <2200)
            {
                UART_Printf("\n\r Do nothing");
            }
            else
            {
                OCR1A = ICR1 - pulse_width;
            }
            UART_Printf("\n\r servo right\n\r");
        }
        else if (min_value == ADCvalue3)
        {

            UART_Printf("\n\r stepper left\n\r");
        }

    }
    else if ( min_value1==ADCvalue2)
    {
        min_value= MIN(ADCvalue1,ADCvalue3);
        if((ADCvalue0==0)&&(ADCvalue1==0)&&(ADCvalue3==0))
        {
            UART_Printf("\n\rLIGHT HAS BEEN FOUND\n\r");
        }
        else if(min_value == ADCvalue3)
        {

            pulse_width +=200;
            if(pulse_width >4000)
            {
                UART_Printf("\n\r Do nothing");
            }
            else
            {
                OCR1A = ICR1 - pulse_width;
            }
            UART_Printf("\n\r servo left\n\r");
        }
        else if (min_value == ADCvalue1)
        {

            UART_Printf("\n\r stepper left\n\r");
        }


    }
    else if(min_value1==ADCvalue3)
    {
          min_value= MIN(ADCvalue2,ADCvalue0);
        if((ADCvalue1==0)&&(ADCvalue2==0)&&(ADCvalue0==0))
        {
            UART_Printf("\n\rLIGHT HAS BEEN FOUND\n\r");
        }
        else if(min_value == ADCvalue2)
        {
            pulse_width +=200;
            if(pulse_width >4000)
            {
                UART_Printf("\n\r Do nothing");
            }
            else
            {
                OCR1A = ICR1 - pulse_width;
            }
            UART_Printf("\n\r servo left\n\r");
        }

        else if (min_value == ADCvalue0)
        {

            UART_Printf("\n\r stepper right\n\r");
        }

    }

    }
    else{

          UART_Printf("\n\r NOTHING DETECTED\n\r");
    }

}
