/******************************************************************************
 *
 * [FILE NAME]:     keypad.h
 *
 * [AUTHOR]:        Omar Amr
 *
 * [DATE]:          11-10-2022
 *
 * [DESCRIPTION]:   Source file for keypad Driver
 *
 *******************************************************************************/

#include "../../MCAL/GPIO/gpio.h"
#include "keypad.h"
#include <util/delay.h>


/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

/*
 * Description :
 * Get the Keypad pressed button
 */
static uint8 getButtonChar(uint8 button_number);

/*
 * Description :
 * Initialize Keypad ports and pins
 */
static void KEYPAD_init(void);

/*******************************************************************************
 *                     		 Functions Definitions                             *
 *******************************************************************************/

/*
 * Description :
 * Initialize Keypad ports and pins
 */
static void KEYPAD_init(void){
	GPIO_setupNibbleDirection(KEYPAD_ROWS_PORT_ID, NIBBLE_INPUT, KEYPAD_ROW_1_PIN_ID);
#if (KEYPAD_NUM_COLS == 4)
	GPIO_setupNibbleDirection(KEYPAD_COLS_PORT_ID, NIBBLE_INPUT , KEYPAD_COL_1_PIN_ID);
#else
	GPIO_setupPinDirection(KEYPAD_COLS_PORT_ID, KEYPAD_COL_1_PIN_ID, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COLS_PORT_ID, KEYPAD_COL_1_PIN_ID + 1, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COLS_PORT_ID, KEYPAD_COL_1_PIN_ID + 2, PIN_INPUT);
#endif
}

/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 KEYPAD_getPressedKey(void){
	uint8 row_number, column_number, button_number;
	KEYPAD_init(); /*Keypad must be initialized each time before it is used*/
	while(1){

		for(row_number = 0; row_number< KEYPAD_NUM_ROWS;row_number++){

			/* All keypad port are input pins, except this row will be output pin*/
			GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID, KEYPAD_ROW_1_PIN_ID + row_number, PIN_OUTPUT);

			/* write output to the row output pin (PullUp = Logic low, PullDown = Logic High)  */
			GPIO_writePin(KEYPAD_ROWS_PORT_ID, KEYPAD_ROW_1_PIN_ID + row_number, KEYPAD_LOGIC_CHECK);

			for(column_number = 0; column_number< KEYPAD_NUM_COLS;column_number++){

				button_number = KEYPAD_NUM_COLS * row_number + column_number + 1;

				/* Check if the button is pressed in this column */
				if(GPIO_readPin(KEYPAD_COLS_PORT_ID, KEYPAD_COL_1_PIN_ID + column_number) == KEYPAD_LOGIC_CHECK){
					return getButtonChar(button_number);
				}
			}
			GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID, KEYPAD_ROW_1_PIN_ID + row_number, PIN_INPUT);
		}
	}
}

/*
 * Description :
 * Get the keypad pressed button value according to the selected configuration.
 */
static uint8 getButtonChar(uint8 button_number){
	uint8 button_character;
	switch(button_number){
	case 1:
		button_character = KEYPAD_BUTTON_1;
		break;
	case 2:
		button_character = KEYPAD_BUTTON_2;
		break;
	case 3:
		button_character = KEYPAD_BUTTON_3;
		break;
	case 4:
		button_character = KEYPAD_BUTTON_4;
		break;
	case 5:
		button_character = KEYPAD_BUTTON_5;
		break;
	case 6:
		button_character = KEYPAD_BUTTON_6;
		break;
	case 7:
		button_character = KEYPAD_BUTTON_7;
		break;
	case 8:
		button_character = KEYPAD_BUTTON_8;
		break;
	case 9:
		button_character = KEYPAD_BUTTON_9;
		break;
	case 10:
		button_character = KEYPAD_BUTTON_10;
		break;
	case 11:
		button_character = KEYPAD_BUTTON_11;
		break;
	case 12:
		button_character = KEYPAD_BUTTON_12;
		break;
#if (KEYPAD_NUM_COLS == 4)
	case 13:
		button_character = KEYPAD_BUTTON_13;
		break;
	case 14:
		button_character = KEYPAD_BUTTON_14;
		break;
	case 15:
		button_character = KEYPAD_BUTTON_15;
		break;
	case 16:
		button_character = KEYPAD_BUTTON_16;
		break;
#endif
	default:
		button_character = button_number;
		break;
	}
	return button_character;
}
