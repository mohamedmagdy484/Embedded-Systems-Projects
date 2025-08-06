/*
 * timer1.c
 *
 *  Created on: Aug 1, 2025
 *      Author: SIGMA
 */

#ifndef MCAL_TIMER1_C_
#define MCAL_TIMER1_C_
#include<avr/io.h>

void Timer1_init(void) {
	TCCR1A = (1 << FOC1A);
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS12) | (1 << CS10);
	ICR1 = 7813;
	TIMSK |= (1 << OCIE1A);
	TCNT1 = 0;
}

#endif /* MCAL_TIMER1_C_ */
