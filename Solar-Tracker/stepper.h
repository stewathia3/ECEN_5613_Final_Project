/*
 * Sanjana Tewathia
 * ECEN 5613 - Fall 2020 - Prof. McClure
 * University of Colorado Boulder
 * Revised 12/6/20
 *
 * C include file for the stepper motor driver
 */

#ifndef STEPPER_H_INCLUDED
#define STEPPER_H_INCLUDED
#define AIN1 5
#define AIN2 6
#define BIN1 7
#define BIN2 0

#define DELAY 1

/****************************************************************************************************************
@function: void stepper_init(): initializes stepper motor
@param :    void
@return:    void
*****************************************************************************************************/
void init_stepper();
/****************************************************************************************************************
@function: void stepper_loop): runs the code for stepper to move in desired directions
@param :    void
@return:    void
*****************************************************************************************************/
void stepper_loop();

#endif // STEPPER_H_INCLUDED


