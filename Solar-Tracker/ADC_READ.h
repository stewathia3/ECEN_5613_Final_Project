/*
 * Maitreyee Rao
 * ECEN 5613 - Fall 2020 - Prof. McClure
 * University of Colorado Boulder
 * Revised 12/6/20
 *
 * C include file for the ADC_Read interface is included in ADC_READ.c
 *
 */

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

/****************************************************************************************************************
@function: int ADC_READ(uint8_t adcpin): read adc value at the pin
@param :    adcpin : integer value , adc pin to which the ADC input connected
@return:    integer value that it read from ADC
*****************************************************************************************************/
int ADC_READ(uint8_t adcpin);

/****************************************************************************************************************
@function: void quadphoto_predict(): get values from quad photodiode
@param :    void
@return:    void
*****************************************************************************************************/
void quadphoto_predict();
#endif // ADC_READ_H_INCLUDED
