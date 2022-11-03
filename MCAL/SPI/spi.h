/******************************************************************************
 *
 * [FILE NAME]:     spi.h
 *
 * [AUTHOR]:        Omar Amr
 *
 * [DATE]:          13-10-2022
 *
 * [Description]:   Header file for Serial Peripheral Interface
 *
 * [TARGET HW]:		ATmega32
 *
 *******************************************************************************/

#ifndef SPI_H_
#define SPI_H_

#include "../../Utils/std_types.h"
#include "../../Utils/common_macros.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * Default SPI data value used in case we need to receive a byte from the other device,
 * without need to send a data to it
 */
#define SPI_DEFAULT_DATA_VALUE 		0xFF
#define SPI_TERMINATOR_CHARACTER 	'#'

/*determine how the clock starts*/
typedef enum 
{
	RISING, FALLING
}SPI_ClockPolarity;

typedef enum
{
	SAMPLE, SETUP
}SPI_ClockPhase;

typedef enum
{
	FOSC_4, FOSC_16, FOSC_64, FOSC_128, FOSC_2, FOSC_8, FOSC_32
}SPI_ClockRate;

/*determine which data is sent first*/
typedef enum 
{
	MSB, LSB
}SPI_DataOrder;

typedef enum
{
	SLAVE, MASTER
}SPI_Mode;

typedef struct
{
	SPI_Mode device_mode;
	SPI_ClockPolarity leading_edge;
	SPI_ClockPhase leading_edge_functionality;
	SPI_ClockRate clock_frequency;
	SPI_DataOrder first_data_word;
}SPI_TypeConfig;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the SPI device.
 */
void SPI_init(SPI_TypeConfig * a_spiConfigPtr);

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data);

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 *str);

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 *str);

#endif /*SPI_H_*/
