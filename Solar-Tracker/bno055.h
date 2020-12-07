#ifndef BNO055_H_INCLUDED
#define BNO055_H_INCLUDED

#include "Test_BNO055.h"

/****************************************************************************************************************
@function: void BNO_Calib(void): Caliberate the IMU
@param :   void
@return:   void
*****************************************************************************************************/
void BNO_Calib(void);

/****************************************************************************************************************
@function: void BNO_Euler_data(): Get Euler angles
@param :   void
@return:   void
*****************************************************************************************************/
void BNO_Euler_data();
#endif // BNO055_H_INCLUDED
