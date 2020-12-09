/*
 * Maitreyee Rao
 * ECEN 5613 - Fall 2020 - Prof. McClure
 * University of Colorado Boulder
 * Revised 12/6/20
 *
 * Find definitions for the functions in i2c.h
 *
 * Note: This library was built with reference to I2c library at
 * https://github.com/ExploreEmbedded/ATmega32_ExploreUltraAvrDevKit/archive/master.zip
 *
 */

#include <inttypes.h>
#include <compat/twi.h>
#include "i2c.h"

/*************************************************************************
 Initialization I2C
*************************************************************************/
void init_i2c(void)
{
	TWSR = 0x00;	//set presca1er bits to zero
	TWBR = 0x46;	//SCL frequency is 100K for 16Mhz
	TWCR = 0x04;	//enab1e TWI module
}

/*************************************************************************
Implements I2c start condition
*************************************************************************/
unsigned char start_i2c(unsigned char address)
{
	uint8_t stat;

	// send START condition
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	// wait until transmission completed
	while (!(TWCR &(1 << TWINT)));

	// check value of  Status Register.
	stat = TW_STATUS &0xF8;
	if ((stat != TW_START) && (stat != TW_REP_START)) return 1;

	// send device address
	TWDR = address;
	TWCR = (1 << TWINT) | (1 << TWEN);

	// wail until transmission completed and ACK/NACK has been received
	while (!(TWCR &(1 << TWINT)));

	// check value of TWI Status Register. Mask prescaler bits.
	stat = TW_STATUS &0xF8;
	if ((stat != TW_MT_SLA_ACK) && (stat != TW_MR_SLA_ACK)) return 1;

	return 0;

}

/*************************************************************************

 @brief sends a start condition ,address and transfer direction and waits

 @param    address address and transfer direction of I2C device
 @return   none

*************************************************************************/
void start_wait_i2c(unsigned char address)
{
	uint8_t stat;

	while (1)
	{
		// send START condition
		TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

		// waitfor transmission to be completed
		while (!(TWCR &(1 << TWINT)));

		// check value of TWI Status Register.
		stat = TW_STATUS &0xF8;
		if ((stat != TW_START) && (stat != TW_REP_START)) continue;

		// send device address
		TWDR = address;
		TWCR = (1 << TWINT) | (1 << TWEN);

		// wail until transmission completed
		while (!(TWCR &(1 << TWINT)));

		// check value of TWI Status Register.
		stat = TW_STATUS &0xF8;
		if ((stat == TW_MT_SLA_NACK) || (stat == TW_MR_DATA_NACK))
		{
			/*device busy, send stop condition to terminate write operation */
			TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

			// wait until stop condition is executed and bus released
			while (TWCR &(1 << TWSTO));

			continue;
		}

		//if(stat != TW_MT_SLA_ACK) return 1;
		break;
	}
}

/*************************************************************************
 @brief sends a repeated start condition and sends address
 @param   address address and transfer direction of I2C device
 @return   0   if device is accessible
 @return   1   if device is not accessible
*************************************************************************/
unsigned char repeat_start_i2c(unsigned char address)
{
	return start_i2c(address);

}

/*************************************************************************

 @brief stops the i2c interface
 @return none
*************************************************************************/
void stop_i2c(void)
{
	/*send stop condition */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

	// wait until stop condition is executed
	while (TWCR &(1 << TWSTO));

}

/**********************************************************************
 @brief    Write one byte to I2C device
 @param    data  byte to be transfered
 @return   0   if device is accessible
 @return   1   if device is not accessible
 ********************************************************************/
unsigned char write_i2c(unsigned char data)
{
	uint8_t stat;

	// send data to the previously addressed device

	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);

	// wait until transmission completed
	while (!(TWCR &(1 << TWINT)));

	// check value of TWI Status Register. Mask prescaler bits
	stat = TW_STATUS &0xF8;
	if (stat != TW_MT_DATA_ACK) return 1;
	return 0;

}

/*************************************************************************************************8
 @brief    read one byte from the I2C device, request acknowledgement data from device
 @return   byte read from I2C device
 ****************************************************************************************************/
unsigned char readAck_i2c(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while (!(TWCR &(1 << TWINT)));

	return TWDR;

}

/*************************************************************************************************
 @brief    read one byte from the I2C device, read is followed by a stop condition
 @return   byte read from I2C device
 ********************************************************************************************/
unsigned char readNak_i2c(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR &(1 << TWINT)));

	return TWDR;

}
