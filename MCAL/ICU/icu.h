/******************************************************************************
 *
 * [FILE NAME]:     icu.h
 *
 * [AUTHOR]:        Omar Amr
 *
 * [DATE]:          04-10-2022
 *
 * [Description]:   Header file for Input Capture Unit driver
 *
 * [TARGET HW]:		ATmega32
 *
 *******************************************************************************/


#ifndef ICU_H_
#define ICU_H_

#include "../../Utils/std_types.h"
#include "../../Utils/common_macros.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*input capture pin definition*/
#define ICP1     6

/*Mapped Peripheral registers addresses definitions*/
#define TCNT1 	(*( (volatile uint16 * const)	0x4C))
#define ICR1  	(*( (volatile uint16 * const)	0x46))
#define DDRD 	(*( (volatile uint8  * const)	0x31))
#define TCCR1A	(*( (volatile uint8  * const)	0x4F))
#define TCCR1B	(*( (volatile uint8  * const)	0x4E))
#define TIMSK 	(*( (volatile uint8  * const)	0x59))

/* TCCR1A bits*/
#define FOC1A   3
#define FOC1B   2

/* TCCR1B bits*/
#define ICES1   6
#define CS12    2
#define CS11    1
#define CS10    0

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*Pre-scaler factors definition.*/
typedef enum{
	 NO_CLK, F_CPU_1, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024, EXT_CLK_RISING, EXT_CLK_FALLING
}ICU_Prescaler;

/*Edge type definitions */
typedef enum{
	FALLING_EDGE, RISING_EDGE
}ICU_EdgeSelect;

/*
 * Structure holds the configuration of the input capture unit:
 * Pre-scaler value.
 * Edge detection type.
 * */
typedef struct {
	ICU_Prescaler prescaler;
	ICU_EdgeSelect edge;

}ICU_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void);

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(const ICU_ConfigType * a_configPtr);

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBackFunc(void (*a_functionAddressPtr) (void));

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(ICU_EdgeSelect a_edgeType);


/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_deInit(void);

#endif /* ICU_H_ */
