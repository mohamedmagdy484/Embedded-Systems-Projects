/*
 * POT.c
 *
 *  Created on: Jul 23, 2025
 *      Author: SIGMA
 */


#include "../MCAL/adc.h"
#include"POT.h"



uint8 POT_SPEED(void)
{
	uint8 speed_value = 0;

	uint16 adc_value = 0;

	/* Read ADC channel where the Pot. is connected */
	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);

	/* Calculate the speed from the ADC value*/
	speed_value = (uint8)(((uint32)adc_value*SENSOR_MAX_SPEED*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));
	return speed_value;
}

