/******************************************************************************
 *
 * [FILE NAME]:     icu.c
 *
 * [AUTHOR]:        Omar Amr
 *
 * [DATE]:          04-10-2022
 *
 * [Description]:   Source file for ADC driver
 *
 * [TARGET HW]:		ATmega32
 *
 *******************************************************************************/

#include <avr/interrupt.h>
#include "icu.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/



/* holds the address of the call back function in the application */
static volatile void (*g_CallBack_Ptr) (void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER1_CAPT_vect){

	if (g_CallBack_Ptr != NULL_PTR){
		(*g_CallBack_Ptr)();
	}
}

/*******************************************************************************
 *                    	  Functions Definitions                                *
 *******************************************************************************/

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(const ICU_ConfigType * a_configuration){

	/* Initially the timer value is 0*/
	TCNT1 = 0;

	/* Initially the input capture register value is 0 */
	ICR1 = 0;

	/*configure input capture pin (ICP1/PD6) as i/p pin*/
	CLEAR_BIT(DDRD,ICP1);

	/*Force Output Compare for Compare units bits are set (Normal Mode = Non-PWM Mode)*/
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);

	/*Configure the Input Capture Edge Select bit*/
	if(a_configuration->edge == RISING_EDGE){
		SET_BIT(TCCR1B,ICES1);
	}
	else{
		CLEAR_BIT(TCCR1B,ICES1);
	}

	/*Enable Input Capture Interrupt*/
	SET_BIT(TIMSK,TICIE1);


	/*insert the required clock value in LSBs (CS10, CS11 and CS12) to start the timer*/
	TCCR1B |= (a_configuration->prescaler);
}

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBackFunc(void (*a_functio_address) (void)){
	/* Save the address of the Call back function in a global variable */
	g_CallBack_Ptr = 	a_functio_address;
}

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(ICU_EdgeSelect a_edge_type){
	if(a_edge_type == RISING_EDGE){
		SET_BIT(TCCR1B,ICES1);
	}
	else{
		CLEAR_BIT(TCCR1B,ICES1);
	}
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void){
	TCNT1 = 0;
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void){
	return ICR1;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_deInit(void){
	/* Clear All Timer1 Registers */
	ICU_clearTimerValue();
	TCCR1A = 0;
	TCCR1B = 0;
	ICR1 = 0;

	/*Disable Input Capture Interrupt*/
	CLEAR_BIT(TIMSK,TICIE1);
}
