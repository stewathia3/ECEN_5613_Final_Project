#ifndef ADC_READ_H_INCLUDED
#define ADC_READ_H_INCLUDED

#include <avr/io.h>
#include "uart.h"

#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>

#include <util/delay.h>

#define MIN(a,b) ((a) < (b)  ? (a) : (b) )
#define MIN_FOUR(a,b,c,d) MIN(a,(MIN(b,MIN(c,d))))
int ADC_READ(uint8_t adcpin);
#endif // ADC_READ_H_INCLUDED
