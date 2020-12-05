

#include <avr/io.h>
#include "uart.h"

#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>

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
