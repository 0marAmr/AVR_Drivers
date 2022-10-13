/******************************************************************************
 *
 * [FILE NAME]:     seven_segment.c
 *
 * [AUTHOR]:        Omar Amr
 *
 * [DATE]:          11-10-2022
 *
 * [DESCRIPTION]:   Source file for 7-Segment Driver
 *
 *******************************************************************************/

#include "../../MCAL/GPIO/gpio.h"
#include "seven_segment.h"

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

/*Description:
 * Function to decode the input to the seven segment display
 * */
#ifndef HARDWARE_DECODER
static uint8 SEGMENT_Decoder(unsigned char number);
#endif

/*******************************************************************************
 *                     		 Functions Definitions                             *
 *******************************************************************************/

void SEGMENT_init(void){
	uint8 i = 0;

#ifdef HARDWARE_DECODER

	GPIO_setupNibbleDirection(SEGMENT_PORT_ID, NIBBLE_OUTPUT, SEGMENT_FIRST_PIN);

#else

	for(i=0; i< SEGMENT_PINS; i++){
		GPIO_setupPinDirection(SEGMENT_PORT_ID, SEGMENT_FIRST_PIN + i , PIN_OUTPUT);
	}

#endif

}

void SEGMENT_displayData(uint8 data){
#ifdef HARDWARE_DECODER

	GPIO_writeNibble(SEGMENT_PORT_ID, data, SEGMENT_FIRST_PIN);
	return;

#else
	GPIO_writePort(SEGMENT_PORT_ID, SEGMENT_Decoder(data));
#endif /*HARDWARE_DECODER*/
}

#ifndef HARDWARE_DECODER

/*Description:
 * Function to decode the input to the seven segment display
 * */
static uint8 SEGMENT_Decoder(unsigned char number){
	switch(number){
	case 0:		
		return SEGMENT_DISPLAY_0;
	case 1:
		return SEGMENT_DISPLAY_1;
	case 2:
		return SEGMENT_DISPLAY_2;
	case 3:
		return SEGMENT_DISPLAY_3;
	case 4:
		return SEGMENT_DISPLAY_4;
	case 5:
		return SEGMENT_DISPLAY_5;
	case 6:
		return SEGMENT_DISPLAY_6;
	case 7:
		return SEGMENT_DISPLAY_7;
	case 8:
		return SEGMENT_DISPLAY_8;
	case 9:
		return SEGMENT_DISPLAY_9;
	default:
		return 0;
	}
}

#endif /*~HARDWARE_DECODER*/
