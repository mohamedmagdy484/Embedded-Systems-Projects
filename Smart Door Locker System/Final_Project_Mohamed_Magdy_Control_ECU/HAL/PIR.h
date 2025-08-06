/*
 * PIR.h
 *
 *  Created on: Jul 9, 2025
 *      Author: Mohamed Magdy
 */

#ifndef HAL_PIR_H_
#define HAL_PIR_H_
#include <avr/io.h>
#include"../common/std_types.h"
// === Configuration Macros ===
#define PIR_PORT    PORTC
#define PIR_PIN_REG PINC
#define PIR_DDR     DDRC
#define PIR_PIN     PC2


void PIR_init(void);
 /*
▪ Description: Function to initialize the PIR driver
▪ Inputs: None
▪ Return: None
*/
uint8 PIR_getState(void);
/*
▪ Description: Function to return PIR State
▪ Inputs: None
▪ Return: uint8
*/

#endif /* HAL_PIR_H_ */
