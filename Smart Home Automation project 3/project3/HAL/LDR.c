
 /******************************************************************************
 *
 * Module: LDR Driver
 *
 *
 *
 *
 *
 * Author: Mohamed Magdy
 *
 *******************************************************************************/














#include "ldr.h"
#include "../MCAL/adc.h"

#define ADC_MAX_VALUE          1023

uint16 LDR_getLightIntensity(void)
{
    uint16 adc_value = ADC_readChannel(LDR_SENSOR_CHANNEL_ID);
    /*after reading the adc channel u have to make the conversion of the adc bits value to a real precentage 3lshan kda*/
    /*ht3ml el 7sba ely t7t dy*/
    float voltage = ((float)adc_value / ADC_MAX_VALUE) * ADC_REF_VOLT_VALUE;
    float light_percentage = (1 - (voltage / LDR_SENSOR_MAX_VOLT_VALUE)) * LDR_SENSOR_MAX_LIGHT_INTENSITY;


    if (light_percentage > 100) light_percentage = 100;
    else if (light_percentage < 0) light_percentage = 0;

    return (uint16)light_percentage;
}
