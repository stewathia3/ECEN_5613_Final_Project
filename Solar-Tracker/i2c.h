/*************************************************************************
* Title:    C include file for the I2C interface is included in i2c.c
* Author:   Maitreyee Rao
* Reference : This library was built with reference to I2c library at
https://github.com/ExploreEmbedded/ATmega32_ExploreUltraAvrDevKit/archive/master.zip
many functions were added as required for the implementation

**************************************************************************/





#ifndef I2C_H_INCLUDED
#define I2C_H_INCLUDED

#include <avr/io.h>

/** defines the data direction */
#define I2C_READ    1

/** defines the data direction */
#define I2C_WRITE   0


/**
 @brief initializes the i2c interface
 @return none
 */
 void init_i2c(void);


/**
 @brief stops the i2c interface
 @return none
 */
 void stop_i2c(void);



/**
 @brief Sends a start condition and transfer direction

 @param    address address of the i2c device
 @return   0   if device is accessible
 @return   1   if device is not accessible
 */
 unsigned char start_i2c(unsigned char address);


/**
 @brief sends a repeated start condition and sends address
 @param   address address and transfer direction of I2C device
 @return   0   if device is accessible
 @return   1   if device is not accessible
 */
 unsigned char repeat_start_i2c(unsigned char address);


/**
 @brief sends a start condition ,address and transfer direction and waits

 @param    address address and transfer direction of I2C device
 @return   none
 */
 void start_wait_i2c(unsigned char address);


/**
 @brief    Write one byte to I2C device
 @param    data  byte to be transfered
 @return   0   if device is accessible
 @return   1   if device is not accessible
 */
 unsigned char write_i2c(unsigned char data);


/**
 @brief    read one byte from the I2C device, request acknowledgement data from device
 @return   byte read from I2C device
 */
 unsigned char readAck_i2c(void);

/**
 @brief    read one byte from the I2C device, read is followed by a stop condition
 @return   byte read from I2C device
 */
 unsigned char readNak_i2c(void);



#endif // I2C_H_INCLUDED
