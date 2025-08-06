/*
 * PIR.c
 *
 *  Created on: Jul 9, 2025
 *      Author: Mohamed Magdy
 */

#include"PIR.h"

void PIR_init(void){
 // Set the sensor pin as input
	PIR_DDR  &= ~(1 << PIR_PIN);
}



uint8 PIR_getState(void){


return (PIR_PIN_REG & (1 << PIR_PIN )) ? LOGIC_HIGH : LOGIC_LOW;
}
