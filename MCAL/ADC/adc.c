/******************************************************************************
 *
 * [FILE NAME]:     adc.c
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

#include "adc.h"

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr){
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 01 to choose AVCC = 5v as reference voltage
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = (Config_Ptr->ref_volt<<6);

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 */
	ADCSRA = (1<<ADEN);
	/*Setting ADC clock. The Clock must be between 50KHz to 200KHz*/
	ADCSRA |= (Config_Ptr->prescaler);

}

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(const ADC_SingleEndedIp channel_number){
	ADMUX = (ADMUX & 0xE0) |  (channel_number & 0x07);/* Input channel number must be from 0 --> 7*/
	SET_BIT(ADCSRA,ADSC);				/*ADC start conversion*/
	while(BIT_IS_CLEAR(ADCSRA,ADIF));	/*wait for the Interrupt flag to be raised (conversion finished) */
	SET_BIT(ADCSRA,ADIF); 				/*clear the interrupt flag*/
	return ADC;
}
