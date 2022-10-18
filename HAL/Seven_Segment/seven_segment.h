/******************************************************************************
 *
 * [FILE NAME]:     seven_segment.h
 *
 * [AUTHOR]:        Omar Amr
 *
 * [DATE]:          11-10-2022
 *
 * [DESCRIPTION]:   Header file for 7-Segment Driver
 *
 *******************************************************************************/

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

#include "../../Utils/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*Segment static configurations*/
#define HARDWARE_DECODER		/*define if you are using a hardware decoder circuit*/
#define SEGMENT_COMMON_ANDODE	/*define if you are using a common anode 7-segment	*/

#define SEGMENT_PORT_ID  	PORTC_ID
#define SEGMENT_FIRST_PIN	PIN0_ID

#ifndef HARDWARE_DECODER
#define SEGMENT_PINS 7
#endif

#ifndef HARDWARE_DECODER

	#ifdef SEGMENT_COMMON_ANDODE

	/*Common anode display numbers decoder combinations*/
		enum{					 //efdcbag
			SEGMENT_DISPLAY_0 = 0b01000000,
			SEGMENT_DISPLAY_1 = 0b11111001,
			SEGMENT_DISPLAY_2 = 0b10100100,
			SEGMENT_DISPLAY_3 = 0b10110000,
			SEGMENT_DISPLAY_4 = 0b10011001,
			SEGMENT_DISPLAY_5 = 0b10010010,
			SEGMENT_DISPLAY_6 = 0b10000010,
			SEGMENT_DISPLAY_7 = 0b11111000,
			SEGMENT_DISPLAY_8 = 0b00000000,
			SEGMENT_DISPLAY_9 = 0b00010000
		};



	#else

	/*Common cathode display numbers decoder combinations*/
		enum {
			SEGMENT_DISPLAY_0 = 0b10111111,
			SEGMENT_DISPLAY_1 = 0b00000110,
			SEGMENT_DISPLAY_2 = 0b01011011,
			SEGMENT_DISPLAY_3 = 0b01001111,
			SEGMENT_DISPLAY_4 = 0b01100110,
			SEGMENT_DISPLAY_5 = 0b01101101,
			SEGMENT_DISPLAY_6 = 0b01111101,
			SEGMENT_DISPLAY_7 = 0b00000111,
			SEGMENT_DISPLAY_8 = 0b11111111,
			SEGMENT_DISPLAY_9 = 0b11101111
		};

	#endif /*SEGMENT_COMMON_ANDODE*/
#endif /*HARDWARE_DECODER*/

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

/*
 * Description:
 * Configure the pins for the seven segment
 */
void SEGMENT_init(void);

/*
 * Description:
 * Display the given data on the segment
 */
void SEGMENT_displayData(uint8 data);
#endif /* SEVEN_SEGMENT_H_ */
