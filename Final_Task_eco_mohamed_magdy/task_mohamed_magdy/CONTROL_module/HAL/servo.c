/*
 * servo.c
 *
 *  Created on: Jul 25, 2025
 *      Author: SIGMA
 */


#include<avr/io.h>
#include"../common/Common_Macros.h"
#include"servo.h"


void servo_init(void){
SET_BIT(servo_ddrx,servo_pin); // at3rf eno output kda
// hard coded settings for timer
TCCR1A|=(1<<COM1B1) |  (1<<WGM11);
TCCR1B|=(1<<CS12) | (1<<WGM12)   | (1<<WGM13);

ICR1=1250;
}

void servo_set_angle(uint8 angle){
	if(angle>180){
		angle=180;
	}
	  uint16_t pulse = 62 + ((uint32_t)angle * (125 - 62)) / 180; //62 for 0 angle and 125 for 180 angle
	    OCR1B = pulse;//compare just to get the right angle u want

}
