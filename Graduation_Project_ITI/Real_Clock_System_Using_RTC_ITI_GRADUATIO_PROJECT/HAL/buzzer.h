 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: Buzzer.h
 *
 * Author: Mohamed Magdy
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_




#include<avr/io.h>


// Define Buzzer Pin and Port
#define BUZZER_PORT PORTD
#define BUZZER_DDR DDRD
#define BUZZER_PIN PD0

// Function Prototypes
void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);

#endif /* BUZZER_H_ */
