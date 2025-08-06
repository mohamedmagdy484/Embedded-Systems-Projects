#ifndef COUNTDOWNH
#define COUNTDOWNH

#include <stdint.h>

extern volatile uint8 hour;
extern volatile uint8 min;
extern volatile uint8 sec;
extern volatile uint8 countdown_done_flag;
extern uint8 intrupt;

void Timer2_init(void);           // Start countdown on Timer2
void Timer_countDown(void);       // Decrement countdown
uint8 move_countdown(void);     // UI for setting countdown
void reset_countdown(void);
#endif /* COUNTDOWNH */
