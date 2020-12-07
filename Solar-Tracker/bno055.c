#include <avr/io.h>
#include "uart.h"

#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>

#include <util/delay.h>

#include "Test_BNO055.h"
#include "bno055.h"
#include "i2c.h"
void BNO_Get_ID(void)
{
	start_wait_i2c(BNO055_ADDRESS+I2C_WRITE);	//Set device address and write mode
	write_i2c(BNO055_CHIP_ID_ADDR);			//Access the Chip  register
	repeat_start_i2c(BNO055_ADDRESS+I2C_READ);		//Set device address and read mode
	data = readNak_i2c();			//Should read 0xA0 according to data sheet
	stop_i2c();
	UART_Printf("\n\r%x:",data);

	start_wait_i2c(BNO055_ADDRESS+I2C_WRITE);	//Set device address and read mode
	write_i2c(BNO055_ACCEL_REV_ID_ADDR);		//Access the Chip ID register
	repeat_start_i2c(BNO055_ADDRESS+I2C_READ);		//Set device address and read mode
	data = readNak_i2c();			//Should read 0xFB  according to data sheet
	stop_i2c();
	UART_Printf("\n\r%x:",data);

	start_wait_i2c(BNO055_ADDRESS+I2C_WRITE);	//Set device address and read mode
	write_i2c(BNO055_MAG_REV_ID_ADDR);		//Access the Chip ID register
	repeat_start_i2c(BNO055_ADDRESS+I2C_READ);		//Set device address and read mode
	data = readNak_i2c();			//Should read 0x32  according to data sheet
	stop_i2c();
	UART_Printf("\n\r%x:",data);

	start_wait_i2c(BNO055_ADDRESS+I2C_WRITE);	//Set device address and read mode
	write_i2c(BNO055_GYRO_REV_ID_ADDR);		//Access the Chip ID register
	repeat_start_i2c(BNO055_ADDRESS+I2C_READ);		//Set device address and read mode
	data = readNak_i2c();			//Should read 0x0F  according to data sheet
	stop_i2c();
	UART_Printf("\n\r%x:",data);
}


void BNO_Calib(void)
{
    char String_Data[16];
    unsigned char calib;
    start_wait_i2c(BNO055_ADDRESS+I2C_WRITE);	//Set device address and read mode
		write_i2c(BNO055_CALIB_STAT_ADDR);
		repeat_start_i2c(BNO055_ADDRESS+I2C_READ);
		calib = readNak_i2c();
		stop_i2c();
    while(calib != 0xFF)
    {
        start_wait_i2c(BNO055_ADDRESS+I2C_WRITE);	//Set device address and read mode
		write_i2c(BNO055_CALIB_STAT_ADDR);
		repeat_start_i2c(BNO055_ADDRESS+I2C_READ);
		calib = readNak_i2c();
		stop_i2c();
		itoa(calib, String_Data, 10);
		UART_Printf(" \n\rCAlib: %x",calib);

    }

}

void BNO_Euler_data()
{

    char String_Data[16];
	unsigned char Euler_Raw_LSB;
	unsigned char Euler_Raw_MSB;



	float angle_scale = 1.0f/16.0f;


		start_wait_i2c(BNO055_ADDRESS+I2C_WRITE);	//Set device address and read mode
		write_i2c(BNO055_EULER_H_LSB_ADDR);		//Access LSB of Heading Euler angle
		repeat_start_i2c(BNO055_ADDRESS+I2C_READ);		//Set device address and read mode
		Euler_Raw_LSB = readNak_i2c();
		stop_i2c();

		start_wait_i2c(BNO055_ADDRESS+I2C_WRITE);	//Set device address and read mode
		write_i2c(BNO055_EULER_H_MSB_ADDR);		   //Access LSB of Heading Euler angle
		repeat_start_i2c(BNO055_ADDRESS+I2C_READ);		//Set device address and read mode
		Euler_Raw_MSB = readNak_i2c();
		stop_i2c();

		int16_t Euler_H_Raw = (Euler_Raw_MSB << 8) | (Euler_Raw_LSB);

		float Euler_H = (float)(Euler_H_Raw) * angle_scale;

		itoa(Euler_H, String_Data, 10);			//Convert integer to string, radix=10
        UART_Printf(",EULER");
		UART_Printf(" %s",String_Data);
		//UART_Printf(String_Data);

		start_wait_i2c(BNO055_ADDRESS+I2C_WRITE);	//Set device address and read mode
		write_i2c(BNO055_EULER_R_LSB_ADDR);		    //Access LSB of Roll Euler angle
		repeat_start_i2c(BNO055_ADDRESS+I2C_READ);		//Set device address and read mode
		Euler_Raw_LSB = readNak_i2c();
		stop_i2c();

		start_wait_i2c(BNO055_ADDRESS+I2C_WRITE);	//Set device address and read mode
		write_i2c(BNO055_EULER_R_MSB_ADDR);		//Access MSB of Roll Euler angle
		repeat_start_i2c(BNO055_ADDRESS+I2C_READ);		//Set device address and read mode
		Euler_Raw_MSB = readNak_i2c();
		stop_i2c();

		int16_t Euler_R_Raw = (Euler_Raw_MSB << 8) | (Euler_Raw_LSB);

		float Euler_R = (float)(Euler_R_Raw) * angle_scale;

		itoa(Euler_R, String_Data, 10);  //convert integer to string, radix=10

		UART_Printf(" %s",String_Data);
		//nRF_Put_String(String_Data);

		start_wait_i2c(BNO055_ADDRESS+I2C_WRITE);	//Set device address and read mode
		write_i2c(BNO055_EULER_P_LSB_ADDR);		//Access LSB of Pitch Euler angle
		repeat_start_i2c(BNO055_ADDRESS+I2C_READ);		//Set device address and read mode
		Euler_Raw_LSB = readNak_i2c();
		stop_i2c();

		start_wait_i2c(BNO055_ADDRESS+I2C_WRITE);	//Set device address and read mode
		write_i2c(BNO055_EULER_P_MSB_ADDR);		//Access LSB of Pitch Euler angle
		repeat_start_i2c(BNO055_ADDRESS+I2C_READ);		//Set device address and read mode
		Euler_Raw_MSB = readNak_i2c();
		stop_i2c();

		int16_t Euler_P_Raw = (Euler_Raw_MSB << 8) | (Euler_Raw_LSB);

		float Euler_P = (float)(Euler_P_Raw) * angle_scale;

		itoa(Euler_P, String_Data, 10);  //convert integer to string, radix=10

		UART_Printf(" %s",String_Data);
}
