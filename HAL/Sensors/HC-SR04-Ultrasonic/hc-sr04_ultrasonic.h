/******************************************************************************
 *
 * [FILE NAME]:     hc-sr04_ultrasonic.h
 *
 * [AUTHOR]:        Omar Amr
 *
 * [DATE]:          17-10-2022
 *
 * [Description]:   Header file for HC-SR04-Ultrasonic sensor driver
 *
 *******************************************************************************/


#ifndef HC_SR04_ULTRASONIC_H_
#define HC_SR04_ULTRASONIC_H_

#include "../../../Utils/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define TRIGGER_PORT_ID			PORTB_ID
#define TRIGGER_PIN_ID 			PIN5_ID
#define NUM_OF_EDGES_TO_DETECT	2

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description:
 * initialize the ultrasonic sensor:
 * 	1- Set the trigger pin direction as output.
 * 	2- configure the input capture unit.
 * 	3- sets the callback function.
 */
void Ultrasonic_init(void);

/*
 * Description :
 * Callback function  that gets the high clock pulse time
 * the value is stored in global variable g_pulseTime
 */
void Ultrasonic_edgeProcessing(void);

/*
 * Description:
 * Triggers the ultrasonic sensor by sending a 10us high pulse through trigger pin.
 */
void Ultrasonic_Trigger(void);

/*
 * Description:
 * Gets the distance measured:
 * 	1- triggers the ultrasonic sensor.
 * 	2- reads the high pulse time and returns the distance.
 * */
uint16 Ultrasonic_readDistance(void);

#endif /* HC_SR04_ULTRASONIC_H_ */
