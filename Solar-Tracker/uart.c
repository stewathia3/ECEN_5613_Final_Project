/*
 *
 *
 *     Author: maitreyee Rao
 *  Find definitions for the functions in uart.h file
 */


#include <stdarg.h>
#include "uart.h"
#include <avr\io.h>
#include "stdutils.h"
//baud rate definitions
#define USART_BR_300		300ul
#define USART_BR_1200		1200ul
#define USART_BR_2400		2400ul
#define USART_BR_4800		4800ul
#define USART_BR_9600		9600ul
#define USART_BR_14400		14400ul
#define USART_BR_19200		19200ul
#define USART_BR_38400		38400ul
#define USART_BR_57600		57600ul

//for compatability
#define UxBRR				UBRR0
#define UxCSRA				UCSR0A
#define UxCSRB				UCSR0B
#define UxCSRC				UCSR0C
#define UxDR				UDR0

//uart for 8-bit, 1stop bit, no parity transmission
void UART_Init(unsigned long baud) {

	//check to see if if rx/tx pins are defined
#if defined(UxTX)								//TX as output
	IO_OUT(UxDDR, UxTX);
#endif

#if defined(UxRX)								//RX as input
	IO_IN(UxDDR, UxRX);
#endif

	/* enable receiver and transmitter */
	UxCSRA=		(1<<U2X0);						//double speed
	UxCSRB=		(0<<RXCIE0) |					//0->disable RX complete interrupt
				(0<<TXCIE0) |					//0->disable TX complete interrupt
				(0<<UDRIE0) |					//0->disable usart data register empty interrupt
#if defined(UxRX)
				(1<<RXEN0) |					//1->enable receiver
#else
				(0<<RXEN0) |					//1->enable receiver
#endif
#if defined(UxTX)
				(1<<TXEN0) |					//1->enable transmitter
#else
				(0<<TXEN0) |					//1->enable transmitter
#endif
				(0<<UCSZ02) |					//char size 0b011->8bit
				(0<<RXB80) |					//receive data bit 8 / 9th data bit received
				(0<<TXB80);						//transmitter data bit 8 / 9th data bit to be sent

	/* set frame format: 8 data, 1 stop bit */
	UxCSRC=		(0<<UMSEL01) | (0<<UMSEL00) |	//00-> asynchronous usart
												//01-> synchronous usart
												//10-> reserved
												//11-> master spi
				(0<<UPM01) | (0<<UPM00) |		//parity check 00-> disabled
												//01-> reserved
												//10-> enabled, even parity
												//11-> enabled, odd parity
				(0<<USBS0) |					//stop bit select. 0->1 bit, 1->2bit
				(1<<UCSZ01) | (1<<UCSZ00) |		//char size.
												//000-> 5-bit
												//001-> 6-bit
												//010-> 7-bit
												//011-> 8-bit
												//100-> reserved
												//101-> reserved
												//110-> reserved
												//111-> 9-bit
				(1<<UCPOL0);					//clock polarity. 0-> rising xck edge. 1-> falling xck edge
	/* baud rate generator */
	//UBRR0H=(unsigned char) (baud >> 8);
	//UBRR0L=(unsigned char) baud;
	UxBRR=F_UART / ((UxCSRA & (1<<U2X0))?8:16) / baud - 1;			//generate baud rate register

	//DDRD |= (1<<5);							//xck as output

}

void UART_PutChar(char data_t) {			//send data
	while (!(UxCSRA & (1<<UDRE0)));			//wait for transmission to end
	UxDR=data_t;									//load up the buffer
	//return 0;									//transmission complete
}

void UART_putString(char * str) {			//put a string
	while (*str)								//if the string isn't empty
		UART_PutChar(*str++);						//send the char and advance the pointer
}

void UART_putline(char * str) {
	UART_putString(str);
	UART_putString("\r\n");
}

char UART_getChar(void) {
	//while (!(UxCSRA & (1<<RXC0))) continue;		//wait for the receive to finish
	return UxDR;									//return the context of uart register
}

//test if uart receiver has data
uint8_t UART_Available(void) {
	return UxCSRA & (1<<RXC0);				//RXC0 set if data is available
}

//test if transmitter is busy
uint8_t UART_Busy(void) {
	return !(UxCSRA & (1<<UDRE0));			//UDRE0 set if tx buffer is empty
}


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
 ***************************************************************************************************/
#if ((Enable_UART_TxNumber==1) || (Enable_UART_TxFloatNumber==1) || (Enable_UART_Printf == 1))
void UART_TxNumber(uint8_t v_numericSystem_u8, uint32_t v_number_u32, uint8_t v_numOfDigitsToTransmit_u8)
{
    uint8_t i=0,a[10];

    if(C_BINARY_U8 == v_numericSystem_u8)
    {
        while(v_numOfDigitsToTransmit_u8!=0)
        {
            /* Start Extracting the bits from the specified bit positions.
             Get the Acsii values of the bits and transmit */
            i = util_GetBitStatus(v_number_u32,(v_numOfDigitsToTransmit_u8-1));
            UART_PutChar(util_Dec2Ascii(i));
            v_numOfDigitsToTransmit_u8--;
        }
    }
    else if(v_number_u32==0)
    {
        /* If the number is zero then update the array with the same for transmitting */
        for(i=0;((i<v_numOfDigitsToTransmit_u8) && (i<C_MaxDigitsToTransmit_U8)) ;i++)
            UART_PutChar('0');
    }
    else
    {
        for(i=0;i<v_numOfDigitsToTransmit_u8;i++)
        {
            /* Continue extracting the digits from right side
               till the Specified v_numOfDigitsToTransmit_u8 */
            if(v_number_u32!=0)
            {
                /* Extract the digits from the number till it becomes zero.
                First get the remainder and divide the number by 10 each time.

                example for Decimal number:
                If v_number_u32 = 123 then extracted remainder will be 3 and number will be 12.
                The process continues till it becomes zero or max digits reached*/
                a[i]=util_GetMod32(v_number_u32,v_numericSystem_u8);
                v_number_u32=v_number_u32/v_numericSystem_u8;
            }
            else if( (v_numOfDigitsToTransmit_u8 == C_DefaultDigitsToTransmit_U8) ||
                    (v_numOfDigitsToTransmit_u8 > C_MaxDigitsToTransmit_U8))
            {
                /* Stop the iteration if the Max number of digits are reached or
                 the user expects exact(Default) digits in the number to be transmitted */
                break;
            }
            else
            {
                /*In case user expects more digits to be transmitted than the actual digits in number,
                  then update the remaining digits with zero.
                Ex: v_number_u32 is 123 and user wants five digits then 00123 has to be transmitted */
                a[i]=0;
            }
        }

        while(i)
        {
            /* Finally get the ascii values of the digits and transmit*/
            UART_PutChar(util_Hex2Ascii(a[i-1]));
            i--;
        }
    }


}
#endif









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
#if (Enable_UART_TxFloatNumber==1)
void UART_TxFloatNumber(float v_floatNumber_f32)
{
	uint32_t v_tempNumber_u32;
	/* Dirty hack to support the floating point by extracting the integer and fractional part.
      1.Type cast the number to int to get the integer part.
	  2.transmit the extracted integer part followed by a decimal point(.).
	  3.Later the integer part is made zero by subtracting with the extracted integer value.
	  4.Finally the fractional part is multiplied by 100000 to support 6-digit precision */

	v_tempNumber_u32 = (uint32_t) v_floatNumber_f32;
	UART_TxNumber(C_DECIMAL_U8,v_tempNumber_u32,C_DefaultDigitsToTransmit_U8);

	UART_PutChar('.');

	v_floatNumber_f32 = v_floatNumber_f32 - v_tempNumber_u32;
	v_tempNumber_u32 = v_floatNumber_f32 * 1000000;
	UART_TxNumber(C_DECIMAL_U8,v_tempNumber_u32,C_DefaultDigitsToTransmit_U8);
}
#endif






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
#if ( Enable_UART_Printf   == 1 )
void UART_Printf(const char *argList, ...)
{
	const char *ptr;
	va_list argp;
	sint16_t v_num_s16;
	sint32_t v_num_s32;
	uint16_t v_num_u16;
	uint32_t v_num_u32;
	char *str;
	char  ch;
	uint8_t v_numOfDigitsToTransmit_u8;
#if (Enable_UART_TxFloatNumber==1)
	double v_floatNum_f32;
#endif


	va_start(argp, argList);

	/* Loop through the list to extract all the input arguments */
	for(ptr = argList; *ptr != '\0'; ptr++)
	{

		ch= *ptr;
		if(ch == '%')         /*Check for '%' as there will be format specifier after it */
		{
		    ptr++;
		    ch = *ptr;
		   if((ch>=0x30) && (ch<=0x39))
			{
			   v_numOfDigitsToTransmit_u8 = 0;
			   while((ch>=0x30) && (ch<=0x39))
			    {
				   v_numOfDigitsToTransmit_u8 = (v_numOfDigitsToTransmit_u8 * 10) + (ch-0x30);
				   ptr++;
				   ch = *ptr;
				}
			}
			else
			{
			  v_numOfDigitsToTransmit_u8 = C_MaxDigitsToTransmitUsingPrintf_U8;
			}


			switch(ch)       /* Decode the type of the argument */
			{
			case 'C':
			case 'c':     /* Argument type is of char, hence read char data from the argp */
				ch = va_arg(argp, int);
				UART_PutChar(ch);
				break;

			case 'd':    /* Argument type is of signed integer, hence read 16bit data from the argp */
				v_num_s16 = va_arg(argp, sint16_t);
				if(v_num_s16<0)
				 { /* If the number is -ve then display the 2's complement along with '-' sign */
				   v_num_s16 = -v_num_s16;
				   UART_PutChar('-');
				 }
				UART_TxNumber(C_DECIMAL_U8,v_num_s16,v_numOfDigitsToTransmit_u8);
				break;

			case 'D':    /* Argument type is of integer, hence read 16bit data from the argp */
				v_num_s32 = va_arg(argp, sint32_t);
				if(v_num_s32<0)
				 { /* If the number is -ve then display the 2's complement along with '-' sign */
				   v_num_s32 = -v_num_s32;
				   UART_PutChar('-');
				 }
				UART_TxNumber(C_DECIMAL_U8,v_num_s32,v_numOfDigitsToTransmit_u8);
				break;

			case 'u':    /* Argument type is of unsigned integer, hence read 16bit unsigned data */
				v_num_u16 = va_arg(argp, uint16_t);
				UART_TxNumber(C_DECIMAL_U8,v_num_u16,v_numOfDigitsToTransmit_u8);
				break;

			case 'U':    /* Argument type is of integer, hence read 32bit unsigend data */
				v_num_u32 = va_arg(argp, uint32_t);
				UART_TxNumber(C_DECIMAL_U8,v_num_u32,v_numOfDigitsToTransmit_u8);
				break;

			case 'x':  /* Argument type is of hex, hence hexadecimal data from the argp */
				v_num_u16 = va_arg(argp, uint16_t);
				UART_TxNumber(C_HEX_U8,v_num_u16,v_numOfDigitsToTransmit_u8);
				break;

			case 'X':  /* Argument type is of hex, hence hexadecimal data from the argp */
				v_num_u32 = va_arg(argp, uint32_t);
				UART_TxNumber(C_HEX_U8,v_num_u32,v_numOfDigitsToTransmit_u8);
				break;


			case 'b':  /* Argument type is of binary,Read int and convert to binary */
				v_num_u16 = va_arg(argp, uint16_t);

				if(v_numOfDigitsToTransmit_u8 == C_MaxDigitsToTransmitUsingPrintf_U8)
				   v_numOfDigitsToTransmit_u8 = 16;

				UART_TxNumber(C_BINARY_U8,v_num_u16,v_numOfDigitsToTransmit_u8);
				break;

			case 'B':  /* Argument type is of binary,Read int and convert to binary */
				v_num_u32 = va_arg(argp, uint32_t);

				if(v_numOfDigitsToTransmit_u8 == C_MaxDigitsToTransmitUsingPrintf_U8)
				   v_numOfDigitsToTransmit_u8 = 32;

				UART_TxNumber(C_BINARY_U8,v_num_u32,v_numOfDigitsToTransmit_u8);
				break;


			case 'F':
			case 'f': /* Argument type is of float, hence read double data from the argp */
#if (Enable_UART_TxFloatNumber==1)
				v_floatNum_f32 = va_arg(argp, double);
				UART_TxFloatNumber(v_floatNum_f32);
#endif
				break;


			case 'S':
			case 's': /* Argument type is of string, hence get the pointer to sting passed */
				str = va_arg(argp, char *);
				UART_putString(str);
				break;

			case '%':
				UART_PutChar('%');
				break;
			}
		}
		else
		{
			/* As '%' is not detected transmit the char passed */
			UART_PutChar(ch);
		}
	}

	va_end(argp);
}
#endif
