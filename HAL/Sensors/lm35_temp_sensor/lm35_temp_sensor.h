/******************************************************************************
 *
 * [FILE NAME]:     lm35_temp_sensor.c
 *
 * [AUTHOR]:        Omar Amr
 *
 * [DATE]:          07-10-2022
 *
 * [Description]:   Source file for  LM35 Temperature Sensor driver
 *
 *******************************************************************************/

#ifndef LM35__TEMP_SENSOR_H_
#define LM35__TEMP_SENSOR_H_

#include "../../../Utils/std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LM35_PIN_ID					PIN0_ID
#define LM35_PORT_ID 				PORTA_ID

#define SENSOR_OUTPUT_CHANNEL_ID 	ADC_ch2
#define SENSOR_MAX_TEMPERATURE		150
#define SENSOR_MAX_VOLTAGE			1.5


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * Function configures the specified input pin for the sensor
 */
void LM35_init(void);

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void);

#endif /*LM35__TEMP_SENSOR_H_*/
