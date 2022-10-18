/******************************************************************************
 *
 * [FILE NAME]:     hc-sr04_ultrasonic.c
 *
 * [AUTHOR]:        Omar Amr
 *
 * [DATE]:          17-10-2022
 *
 * [Description]:   Source file for HC-SR04-Ultrasonic sensor driver
 *
 *******************************************************************************/

#include <util/delay.h>
#include "../../../MCAL/GPIO/gpio.h"
#include "../../../MCAL/ICU/icu.h"
#include "hc-sr04_ultrasonic.h"


/*******************************************************************************
 *                               Global Variables                              *
 *******************************************************************************/

static volatile uint16 	g_pulseTime 	= 0;
static volatile uint8  	g_edgesCount 	= 0;

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
void Ultrasonic_init(void){
	GPIO_setupPinDirection(TRIGGER_PORT_ID, TRIGGER_PIN_ID, PIN_OUTPUT);

	/*configure the input capture unit. */
	ICU_ConfigType icu_configuration ={
			.prescaler = F_CPU_8,
			.edge = RISING_EDGE
	};

	/*initialize the ICU*/
	ICU_init(&icu_configuration);

	/*set the callback function.*/
	ICU_setCallBackFunc(Ultrasonic_edgeProcessing);
}

/*
 * Description:
 * Triggers the ultrasonic sensor by sending a 10us high pulse through trigger pin.
 */
void Ultrasonic_Trigger(void){
	GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_LOW);
}

/*
 * Description:
 * Gets the distance measured:
 * 	1- triggers the ultrasonic sensor.
 * 	2- reads the high pulse time and returns the distance.
 * */
uint16 Ultrasonic_readDistance(void){
	/*start the measurements by the ICU*/
	Ultrasonic_Trigger();

	/*resets the global edges count to start a new*/
	if(g_edgesCount >= NUM_OF_EDGES_TO_DETECT){
		g_edgesCount = 0;
	}

	/*calculate and return the distance in centimeters */
	return (g_pulseTime/58 + 1); /*(adding 1 for value correction)*/
}

/*
 * Description :
 * Callback function  that gets the high clock pulse time
 * the value is stored in global variable g_pulseTime
 */
void Ultrasonic_edgeProcessing(void){
	g_edgesCount++;
	if (g_edgesCount == 1){

		/*get the time after the rising edge*/
		ICU_clearTimerValue();

		/*Detect the falling edge*/
		ICU_setEdgeDetectionType(FALLING_EDGE);
	}
	else if(g_edgesCount == 2){
		/*store high pulse time*/
		g_pulseTime = ICU_getInputCaptureValue();

		/*Detect the rising edge for future measurements*/
		ICU_setEdgeDetectionType(RISING_EDGE);
	}
}
