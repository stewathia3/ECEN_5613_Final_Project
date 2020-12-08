#include <avr/io.h>
#include "uart.h"
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>
#include "stepper.h"

volatile unsigned char step_num = 1;

void step(unsigned char direction);
void init_stepper()
{
    //four coils of stepper set as output
	DDRB |= _BV(AIN1);
	DDRD |= _BV(AIN2);
	DDRD |= _BV(BIN1);
	DDRD |= _BV(BIN2);

}

void stepper_loop()
{
	int i;
	UART_putline("Press a command to turn the motor:\n\r");
	UART_putline(" '1' to step CW 1 step\n\r");
	UART_putline(" '2' to step CCW 1 step\n\r");
	UART_putline(" '3' to step CW 1 rev\n\r");
	UART_putline(" '4' to step CCW 1 rev\n\r");
	unsigned char direction = 1;	// CW = 1, CCW = 0

	if (UART_Available())
	{
		unsigned char command = UART_getChar();
		UART_PutChar(command);
		if (command == '1')
		{
			// Step CW 1 step
			direction = 1;
			step(direction);

		}
		else if (command == '2')
		{
			// Step CCW 1 step
			direction = 0;
			step(direction);

		}
		else if (command == '3')
		{
			// Step CW 200 steps (1 rev)
			direction = 1;
			for (i = 0; i < 200; i++)
			{
				step(direction);
				_delay_ms(DELAY);
			}
		}
		else if (command == '4')
		{
			// Step CCW 200 steps (1 rev)
			direction = 0;
			for (i = 0; i < 200; i++)
			{
				step(direction);
			}
		}
		else
		{
			UART_putline("\n\rInvalid command entered.");
		}
	}
}

void step(unsigned char direction)
{
	if (step_num == 1)
	{
		// 1010 //by setting direction for coils
		PORTD |= _BV(AIN1);
		PORTD &= ~_BV(AIN2);
		PORTD |= _BV(BIN1);
		PORTB &= ~_BV(BIN2);

		if (direction == 1)
		{
			step_num++;
		}
		else
		{
			step_num = 4;
		}
	}
	else if (step_num == 2)
	{
		// 0110 //by setting direction for coils

		PORTD &= ~_BV(AIN1);
		PORTD |= _BV(AIN2);
		PORTD |= _BV(BIN1);
		PORTB &= ~_BV(BIN2);

		if (direction == 1)
		{
			step_num++;
		}
		else
		{
			step_num--;
		}
	}
	else if (step_num == 3)
	{
		// 0101 ///by setting direction for coils
		PORTD &= ~_BV(AIN1);
		PORTD |= _BV(AIN2);
		PORTD &= ~_BV(BIN1);
		PORTB |= _BV(BIN2);

		if (direction == 1)
		{
			step_num++;
		}
		else
		{
			step_num--;
		}
	}
	else
	{
		// (step_num == 4)

		// 1001 ///by setting direction for coils
		PORTD |= _BV(AIN1);
		PORTD &= ~_BV(AIN2);
		PORTD &= ~_BV(BIN1);
		PORTB |= _BV(BIN2);

		if (direction == 1)
		{
			step_num = 1;
		}
		else
		{
			step_num--;
		}
	}
}
