
/*************************************************************************
* Title:    C include file for the UART interface is included in uart.c
 * Author: maitreyee
 * Reference:   code was referenced and modiefied from
 https://exploreembedded.com/wiki/Serial_UART_Interface_with_AVR
**************************************************************************/

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
/****************************************************************************************************************
@function: void UART_Init(unsigned long baud): initializes UART for required baud rate
@param :    baud takes input baud as required baud rate
@return:    void
*****************************************************************************************************/
void UART_Init(unsigned long baud);
/****************************************************************************************************************
@function: void UART_PutChar(char data_t): transmits character over uart
@param :   char data_t character to be transmitted
@return:    void
*****************************************************************************************************/
void UART_PutChar(char data_t);			//send data
/****************************************************************************************************************
@function: void UART_putString(char * str): transmits string over Uart
@param :   str : string to be transmitted
@return:    void
*****************************************************************************************************/
void UART_putString(char * str);			//put a string
/****************************************************************************************************************
@function: void UART_putline(char * str): transmits string over Uart with new line and carriage return
@param :   str : string to be transmitted
@return:    void
*****************************************************************************************************/
void UART_putline(char * str);			//put a string, with line return
/****************************************************************************************************************
@function: void UART_getChar(void): recieve character over UART
@param :   void
@return:    void
*****************************************************************************************************/
char UART_getChar(void);
/****************************************************************************************************************
@function: uint8_t UART_Available(void): check if UART is available to recieve
@param :   void
@return:   1 if available
*****************************************************************************************************/
uint8_t UART_Available(void);
/****************************************************************************************************************
@function: uint8_t bu(void): check if UART is available to recieve
@param :   void
@return:   1 if busy
*****************************************************************************************************/
uint8_t UART_Busy(void);

/***************************************************************************************************
void UART_TxNumber(uint8_t v_numericSystem_u8, uint32_t v_number_u32, uint8_t v_numOfDigitsToTransmit_u8)
 ***************************************************************************************************
 * I/P Arguments:
                  uint8_t :  specifies type of number C_BINARY_U8(2),C_DECIMAL_U8(10), C_HEX_U8(16)
                  uint32_t: Number to be transmitted on UART.
                  uint8_t : Number of digits to be transmitted

 * Return value    : none

 * description  :This function is used to transmit a max of 10digit decimal number.
                2nd parameter specifies the number of digits from the right side to be transmitted
                 The output for the input combinations is as below

    Binary:     1.(10,4) then 4-LSB will be transmitted ie. 1010
                2.(10,8) then 8-LSB will be transmitted ie. 00001010
                3.(10,2) then 2-LSB will be transmitted ie. 10

    Decimal
                4.(12345,4) then 4-digits ie. 2345 will be transmitted
                5.(12345,6) then 6-digits ie. 012345 will be transmitted
                6.(12345,C_DefaultDigitsToTransmit_U8) then 12345 will be transmitted.

    Hex:
                7.(0x12AB,3) then 3-digits ie. 2AB will be transmitted
                8.(0x12AB,6) then 6-digits ie. 0012AB will be transmitted
                9.(0x12AB,C_DefaultDigitsToTransmit_U8) then 12AB will be transmitted.

                this code was referenced from https://exploreembedded.com/wiki/Serial_UART_Interface_with_AVR
 ***************************************************************************************************/

void UART_TxNumber(uint8_t v_numericSystem_u8, uint32_t v_number_u32, uint8_t v_numOfDigitsToTransmit_u8);
/***************************************************************************************************
            void  UART_TxFloatNumber(float v_floatNumber_f32)
 ***************************************************************************************************
 * Function name:  UART_TxFloatNumber()
 * I/P Arguments: float: float Number to be transmitted on UART.

 * Return value	: none

 * description  :This function is used to transmit a floating point number

 * Note         :It supports 6digits of precision.
         Float will be disabled by default as it takes huge controller resources
	     It can be enabled by changing value of Enable_UART_TxFloatNumber to 1 in uart.h
 ***************************************************************************************************/
void UART_TxFloatNumber(float v_floatNumber_f32);

/***************************************************************************************************
            void UART_Printf(const char *argList, ...)
 ***************************************************************************************************
 * Function name:  UART_Printf()
 * I/P Arguments: variable length arguments similar to printf

 * Return value	: none

 * description  :This function is similar to printf function in C.
				 It takes the arguments with specified format and prints accordingly
				 The supported format specifiers are as below.
				 1. %c: character
				 2. %d: signed 16-bit number
				 3. %D: signed 32-bit number
				 4. %u: unsigned 16-bit number
				 5. %U: unsigned 32-bit number
				 6. %b: 16-bit binary number
				 7. %B: 32-bit binary number
				 8. %f: Float number
				 9. %x: 16-bit hexadecimal number
				 10. %X: 32-bit hexadecimal number
				 11. %s: String

  Note: By default all the functions will be disabled. The required functions can be enabled by
        setting the respective compiler switch to 1 in uart.h file.
		Ex:  setting Enable_UART_TxDecimalNumber to 1 will enable %d
		     setting Enable_UART_TxHexNumber to 1 will enable %x

  Extra feature is available to specify the number of digits to be transmitted using printf.
	 ex: %4d: will transmit the lower four digits of the decimal number.
	     %12b: will transmit the 12-LSB of the number
		 %d: Will transmit the exact digits of the number

#####: In case of printing the variables(8-bit) its recommended to type cast and promote them to uint16_t.
        uint8_t v_Num_u8;
		UART_Printf("num1:%u",(uint16_t)v_Num_u8);
***************************************************************************************************/
void UART_Printf(const char *argList, ...);

#endif
