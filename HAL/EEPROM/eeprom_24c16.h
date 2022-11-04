/******************************************************************************
 *
 * [FILE NAME]:     eeprom_24c16.c
 *
 * [AUTHOR]:        Omar Amr
 *
 * [DATE]:          01-11-2022
 *
 * [Description]:   Header file for EEPROM 24C16
 *
 *******************************************************************************/


#ifndef EEPROM__H_
#define EEPROM__H_

#include "../../Utils/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

#endif /* EEPROM__H_ */
