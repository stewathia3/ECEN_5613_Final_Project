
#include <avr/io.h>
#include "uart.h"

#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>

#include <util/delay.h>
#include "servo.h"

#include "Test_BNO055.h"
#include "bno055.h"
#include "i2c.h"
#include "stepper.h"
#include "ADC_READ.h"
#include "easydriver.h"
//Declare variables for functions
char user_input;
int x;
int y;
int state;
void easydriver_init() {

  DDRD |= _BV(stp);
  DDRD |= _BV(dir);
  DDRD |= _BV(MS1);
  DDRD |= _BV(MS2);
  DDRD |= _BV(EN);


  resetEDPins(); //Set step, direction, microstep and enable pins to default states


}

//Reset Easy Driver pins to default states
void resetEDPins()
{
  PORTD &= ~_BV(stp);
  PORTD &= ~_BV(dir);
  PORTD &= ~_BV(MS1);
  PORTD &= ~_BV(MS1);
  PORTD |= _BV(EN);


}

void ForwardOneStep()
{
  UART_Printf("Stepping at 1/8th microstep mode.");
  PORTD |= _BV(EN);
  PORTD &= ~_BV(dir);
  PORTD |= _BV(MS1);
  PORTD |= _BV(MS2);
//  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
//  digitalWrite(MS1, HIGH); //Pull MS1, and MS2 high to set logic to 1/8th microstep resolution
//  digitalWrite(MS2, HIGH);
  for(x= 0; x<100; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    PORTD |= _BV(stp);
    DELAY_ms(DELAY);
    PORTD &= ~_BV(stp);
    DELAY_ms(DELAY);

  }
  UART_Printf("Enter new option\n\r");
}
void BackwardOneStep()
{
  UART_Printf("Stepping at 1/8th microstep mode.");
  PORTD |= _BV(EN);
  PORTD |= _BV(dir);
  PORTD |= _BV(MS1);
  PORTD |= _BV(MS2);
//  digitalWrite(dir, HIGH); //Pull direction pin low to move "forward"
//  digitalWrite(MS1, HIGH); //Pull MS1, and MS2 high to set logic to 1/8th microstep resolution
//  digitalWrite(MS2, HIGH);
  for(x= 0; x<100; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    PORTD |= _BV(stp);
    DELAY_ms(DELAY);
    PORTD &= ~_BV(stp);
    DELAY_ms(DELAY);

  }
//  Serial.println("Enter new option");
//  Serial.println();
}
