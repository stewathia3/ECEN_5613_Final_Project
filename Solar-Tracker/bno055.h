/*
 * Maitreyee Rao
 * ECEN 5613 - Fall 2020 - Prof. McClure
 * University of Colorado Boulder
 * Revised 12/6/20
 *
 * C include file for the BNO005 interface is included in bno005.c
 *
 * Note: Referenced and modified from: https://github.com/adafruit/Adafruit_BNO055/blob/master/Adafruit_BNO055.h
 */

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
