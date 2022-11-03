/******************************************************************************
 *
 * [FILE NAME]:     spi.c
 *
 * [AUTHOR]:        Omar Amr
 *
 * [DATE]:          13-10-2022
 *
 * [Description]:   Source file for Serial Peripheral Interface
 *
 * [TARGET HW]:		ATmega32
 *
 *******************************************************************************/

#include "spi.h"
#include "../GPIO/gpio.h"
#include <avr/io.h>

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the SPI device.
 */
void SPI_init(SPI_TypeConfig * a_spiConfigPtr)
{
	/*pin configurations for master SPI*/
	if(a_spiConfigPtr->device_mode == MASTER)
    {
		GPIO_setupPinDirection(PORTB_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
		GPIO_setupPinDirection(PORTB_ID, PIN6_ID, PIN_INPUT );
		GPIO_setupPinDirection(PORTB_ID, PIN7_ID, PIN_OUTPUT);
	}
	/*pin configurations for slave SPI*/
	else if(a_spiConfigPtr->device_mode == SLAVE)
    {
		GPIO_setupPinDirection(PORTB_ID, PIN4_ID, PIN_INPUT);
		GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_INPUT);
		GPIO_setupPinDirection(PORTB_ID, PIN6_ID, PIN_OUTPUT);
		GPIO_setupPinDirection(PORTB_ID, PIN7_ID, PIN_INPUT);
	}

	/************************** SPCR Description **************************
	 * SPIE     	SPI Interrupt Enable
	 * SPE      	SPI Enable
	 * DORD     	Data Order
	 * MSTR    		Master/Slave select
	 * CPOL    		Clock Polarity (first edge rising/falling)
	 * CPHA    		Clock phase (Sample Data with the leading/trailing)
	 * SPR1:0  		SPI clock rate (prescaler)
	 ***********************************************************************/
	SPCR =  (1 << SPE) | (a_spiConfigPtr->first_data_word << DORD)\
			| (a_spiConfigPtr->device_mode << MSTR) | (a_spiConfigPtr->leading_edge << CPOL)\
			|(a_spiConfigPtr->leading_edge_functionality << CPHA)\
			| (a_spiConfigPtr->clock_frequency << SPR0);

	/*
	 * Double speed mode:
	 * disabled since the SPI is grunted to work @ fosc/4
	 * */
	CLEAR_BIT(SPSR,SPI2X);
}

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 a_data)
{
	/* Initiate the communication and send data by SPI */
	SPDR = a_data;

	/* Wait until =data has been sent/received correctly */
	while(BIT_IS_CLEAR(SPSR,SPIF));

	/*SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR.*/
	return SPDR;
}

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 * a_strPtr)
{
	uint8 i =0;

	/* Send the whole string */
	while(a_strPtr[i] != '\0')
	{
		SPI_sendReceiveByte(a_strPtr[i]);
		i++;
	}
}

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 * const a_strPtr)
{
	uint8 i = 0;

	/* Receive the first byte */
	do
	{
		/* Receive the whole string until reaching the SPI_TERMINATOR_CHARACTER */
		a_strPtr[i]	= SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
	}
	while(a_strPtr[i++] != SPI_TERMINATOR_CHARACTER);

	/* replace the SPI_TERMINATOR_CHARACTER with '\0' */
	a_strPtr[i-1] = '\0';
}
