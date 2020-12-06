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

void servo_init();
void servo_left();
void servo_right();
#endif // SERVO_H_INCLUDED
