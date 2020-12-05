

#include <avr/io.h>
#include "uart.h"

#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>
#include "ADC_READ.h"

#include <util/delay.h>
/*************************************************************************************/

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

         ADCvalue0 = ADC_READ(0);
         ADCvalue1 = ADC_READ(1);
         ADCvalue2 = ADC_READ(2);
         ADCvalue3 = ADC_READ(3);

    min_value= MIN_FOUR(ADCvalue0,ADCvalue1,ADCvalue2,ADCvalue3);

    if(min_value == ADCvalue0)
    {


    }
    else if(min_value == ADCvalue1)
    {


    }
    else if (min_value == ADCvalue2)
    {


    }
    else if(min_value == ADCvalue3)
    {

    }


}
