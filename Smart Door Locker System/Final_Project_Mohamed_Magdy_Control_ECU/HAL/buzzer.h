#ifndef BUZZER_H_
#define BUZZER_H_
#include<avr/io.h>
// Define Buzzer Pin and Port
#define BUZZER_PORT PORTC
#define BUZZER_DDR DDRC
#define BUZZER_PIN PC7

// Function Prototypes
void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);

#endif /* BUZZER_H_ */
