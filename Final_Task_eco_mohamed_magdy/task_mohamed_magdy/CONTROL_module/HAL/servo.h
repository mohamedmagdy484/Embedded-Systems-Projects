/*
 * servo.h
 *
 *  Created on: Jul 25, 2025
 *      Author: SIGMA
 */

#ifndef SERVO_H_
#define SERVO_H_
#include<avr/io.h>
#include"../common/Common_Macros.h"
#include"../common/std_types.h"

#define servo_ddrx DDRD
#define servo_pin  PD4
#define servo_port PORTD


void servo_init(void);
void servo_set_angle(uint8 angle);







#endif /* SERVO_H_ */
