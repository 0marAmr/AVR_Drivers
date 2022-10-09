/******************************************************************************
 *
 * [FILE NAME]:     lm35_temp_sensor.h
 *
 * [AUTHOR]:        Omar Amr
 *
 * [DATE]:          07-10-2022
 *
 * [Description]:   Header file for  LM35 Temperature Sensor driver
 *
 *******************************************************************************/

#include "../../../MCAL/ADC/adc.h"
#include "lm35_temp_sensor.h"


/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void){
	uint8 temp_value = 0;
	uint16 adc_temp_read = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc_temp_read = ADC_readChannel(SENSOR_OUTPUT_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((uint32)adc_temp_read * SENSOR_MAX_TEMPERATURE * ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE * SENSOR_MAX_VOLTAGE));

	return temp_value;
}

