/*
 * Maitreyee Rao, Sanjana Tewathia
 * ECEN 5613 - Fall 2020 - Prof. McClure
 * University of Colorado Boulder
 * Revised 12/6/20
 *
 * C include file for the base_servo interface is included in base_servo.c
 *
 * Note: Referenced and modified using: https://sites.google.com/site/qeewiki/books/avr-guide/pwm-atmega8
 */

#ifndef BASE_SERVO_H_INCLUDED
#define BASE_SERVO_H_INCLUDED

#include <avr/io.h>
#include "uart.h"
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>
#include "ADC_READ.h"
#include <util/delay.h>
#include "Test_BNO055.h"
#include "bno055.h"
#include "i2c.h"
/****************************************************************************************************************
@function: void base_servo_left(): turns base servo to left
@param :   void
@return:   void
*****************************************************************************************************/
void base_servo_left();
/****************************************************************************************************************
@function: void base_servo_right(): turns base servo to right
@param :   void
@return:   void
*****************************************************************************************************/
void base_servo_right();


#endif // BASE_SERVO_H_INCLUDED
