/*
 * test.c
 *
 *  Created on: Dec 4, 2020
 *      Author: maitr
 */


#ifndef _UART_H
#define _UART_H


#include "gpio.h"						//we use gpio
#include "stdutils.h"

#define    Enable_UART_TxNumber          1
#define    Enable_UART_TxFloatNumber     1
#define    Enable_UART_Printf            1
/**************************************************************************************************/





/***************************************************************************************************
                             Commonly used UART macros/Constants
***************************************************************************************************/
#define C_DefaultDigitsToTransmit_U8          0xffu    // Will transmit the exact digits in the number
#define C_MaxDigitsToTransmit_U8              10u      // Max decimal/hexadecimal digits to be transmitted
#define C_NumOfBinDigitsToTransmit_U8         16u      // Max bits of a binary number to be transmitted
#define C_MaxDigitsToTransmitUsingPrintf_U8   C_DefaultDigitsToTransmit_U8 /* Max dec/hexadecimal digits to be displayed using printf */
/**************************************************************************************************/


//hardware configuration
//#define UxPORT				PORTB
#define UxDDR				DDRB
#define UxTX				(1<<0)		//comment out if not used
#define UxRX				(1<<1)		//comment out if not used
#define    Enable_UART_Printf            1

//end hardware configuration


//baud rate definitions
#define F_UART				(F_CPU)		//8Mhz		//crystal frequency
#define UART_BR_300			300ul		//buadrate=300
#define UART_BR_600			600ul		//buadrate=600
#define UART_BR_1200		1200ul		//buadrate=1200
#define UART_BR_2400		2400ul		//buadrate=2400
#define UART_BR_4800		4800ul		//buadrate=4800
#define UART_BR_9600		9600ul		//buadrate=9600
#define UART_BR_19200		19200ul		//buadrate=19200
#define UART_BR_38400		38400ul		//buadrate=38400
#define UART_BR_57600		57600ul		//buadrate=57600
#define UART_BR_115200		115200ul	//buadrate=115200

#define uart_put(n)			UART_TxChar(n)
#define uart_get()			UART_RxChar()

void UART_Init(unsigned long baud);

void UART_PutChar(char data_t);			//send data

void UART_putString(char * str);			//put a string

void UART_putline(char * str);			//put a string, with line return

char UART_getChar(void);					//get a char from uart

//test if uart receiver has data
uint8_t UART_Available(void);
//#define UART_Availablr()	(UCSR0A & (1<<RXC0))

//test if transmitter is busy
uint8_t UART_Busy(void);
//#define UART_Busy()			(!(UCSR0A & (1<<UDRE0)))

void UART_TxNumber(uint8_t v_numericSystem_u8, uint32_t v_number_u32, uint8_t v_numOfDigitsToTransmit_u8);
void UART_TxFloatNumber(float v_floatNumber_f32);
void UART_Printf(const char *argList, ...);

#endif
