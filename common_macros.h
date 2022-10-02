 /******************************************************************************
 *
 * [FILE NAME]:     common_macros.h
 * 
 * [AUTHOR]:        Omar Amr
 *
 * [DATE]:          01-10-2022
 * 
 * [Description]:   Commonly used Macros
 *
 *******************************************************************************/

#ifndef COMMON_MACHROS_H_
#define COMMON_MACHROS_H_

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT){\
(REG) = ((REG) | (1<<(BIT)));\
}\

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT){\
(REG) = ((REG) & ~(1<<(BIT)));\
}\

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT){\
(REG) = ((REG) ^ (1<<BIT));\
}\

/* Get the value of a specific bit in a given register*/
#define GET_BIT(REG,BIT)(((REG)&(1<<(BIT)))>>(BIT))

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,BIT){\
REG = ((REG)<<(BIT)) | ((REG)>>(REG_SIZE-BIT));\
}\

/* Rotate right the register value with specific number of rotates */
#define  ROR(REG,BIT){\
REG = ((REG)>>(BIT)) | ((REG)<<(REG_SIZE-BIT));\
}\

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#endif /*COMMON_MACHROS_H_*/
