/******************************************************************************
 *
 * [FILE NAME]:     adc.h
 *
 * [AUTHOR]:        Omar Amr
 *
 * [DATE]:          01-10-2022
 *
 * [Description]:   Header file for ADC driver
 *
 * [TARGET HW]:		ATmega32
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "common_macros.h"
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*Mapped Peripheral registers addresses definitions*/
#define ADMUX 	(*( (volatile uint8 * const) 	0x27))
#define ADCSRA 	(*( (volatile uint8 * const) 	0x26))
#define ADC 	(*( (volatile uint16 * const) 	0x24))

/*Bits Definitions */
/* ADCSRA */
#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0

/* ADMUX */
#define REFS1   7
#define REFS0   6
#define ADLAR   5
#define MUX4    4
#define MUX3    3
#define MUX2    2
#define MUX1    1
#define MUX0    0

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/* ADC Vref source type*/
typedef enum{
	ADC_ExternalAREF,				/*External reference voltage on AREF pin */
	ADC_AVcc,						/*Analog Vcc which is 5 volts*/
	/*10 combination is reserved*/
	ADC_InternalVoltageRef = 3,		/* 2.56 internal voltage*/
}ADC_ReferenceVolatge;

/*Pre-scaler factors definition.*/
typedef enum{
	 F_CPU_2 = 1, F_CPU_4, F_CPU_8, F_CPU_16, F_CPU_32, F_CPU_64, F_CPU_128
}ADC_Prescaler;

/*ADC input channels*/
typedef enum{
	ADC_ch0, ADC_ch1, ADC_ch2, ADC_ch3, ADC_ch4, ADC_ch5, ADC_ch6, ADC_ch7
}ADC_SingleEndedIp;

/*Structure contains the configuration of ADC: Pre-scaler and reference voltage choice*/
typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(const ADC_SingleEndedIp channel_number);


#endif
