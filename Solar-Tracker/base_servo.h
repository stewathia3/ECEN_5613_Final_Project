#ifndef BASE_SERVO_H_INCLUDED
#define BASE_SERVO_H_INCLUDED

#ifndef SERVO_1_H_INCLUDED
#define SERVO_1_H_INCLUDED

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

void base_servo_left();
void base_servo_right();




#endif // SERVO_1_H_INCLUDED


#endif // BASE_SERVO_H_INCLUDED