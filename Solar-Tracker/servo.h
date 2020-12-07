#ifndef SERVO_H_INCLUDED
#define SERVO_H_INCLUDED


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
@function: void servo_init(): initializes PWM pins, timer and gpio
@param :    void
@return:    void
*****************************************************************************************************/
void servo_init();
/****************************************************************************************************************
@function: void servo_left(): turns servo to left
@param :    void
@return:    void
*****************************************************************************************************/
void servo_left();
/****************************************************************************************************************
@function: void servo_right(): turns servo to the right
@param :    void
@return:    void
*****************************************************************************************************/
void servo_right();
#endif // SERVO_H_INCLUDED
