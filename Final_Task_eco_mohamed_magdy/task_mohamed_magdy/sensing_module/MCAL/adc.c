/*
 * -----------------------------------------------------------------------------------------------------------------------
 * --------------------------------------------- Mohamed_Magdy_Task ------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------------------------
 */

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "../COMMON/common_macros.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(void)
{
	ADMUX = (1 << REFS1) | (1 << REFS0) ;  // Internal 2.56V reference

	ADCSRA = (1<<ADEN) | (0<<ADPS2) | (1<<ADPS1) | (0<<ADPS0);  // F_CPU / 128
}

uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
