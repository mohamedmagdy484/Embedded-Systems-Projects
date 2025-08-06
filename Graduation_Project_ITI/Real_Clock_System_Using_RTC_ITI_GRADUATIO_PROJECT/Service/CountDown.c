#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../HAL/lcd.h"
#include "../HAL/buzzer.h"
#include "countdown.h"
#include"service.h"
volatile uint8 hour = 0, min = 0, sec = 0;   // countdown values
volatile uint8 countdown_done_flag = 0;
uint8 moverr = 0;       // for setting hours/min/sec
uint8 intrupt = 0;     // flag to enable countdown
volatile uint16 tick_count = 0;


#define HOURF    0
#define MINUTEF  1
#define SECONDF  2
#define LOGF     3
// ---------------- Countdown logic ----------------
void Timer_countDown(void) {
	if (!intrupt || countdown_done_flag) return;  // only count if active

	if (sec > 0) sec--;
	else {
		if (min > 0) {
			min--; sec = 59;
		} else {
			if (hour > 0) {
				hour--; min = 59; sec = 59;
			} else {
				// Finished
				sec = min = hour = 0;
				countdown_done_flag = 1;
				Buzzer_on();
			}
		}
	}
}

// ---------------- Timer2 for 1-sec tick ----------------
void Timer2_init(void) {
	TCCR2 = (1 << WGM21) | (1 << CS22) | (1 << CS21) | (1 << CS20); // CTC mode, 1024 prescaler
	OCR2 = 125;             // ~1s at 8MHz with 1024 prescaler
	TIMSK |= (1 << OCIE2);  // Enable compare match
	TCNT2 = 0;
	// Enable countdown
}

// Timer2 ISR -> call countdown
ISR(TIMER2_COMP_vect) {
	tick_count++;
	if (tick_count >= 62) {  // ~62 × 16ms ≈ 1 sec
		tick_count = 0;
		Timer_countDown();
	}}

// ---------------- Time setting mode ----------------
uint8_t move_countdown(void)
{
    if (!(PINB & (1<<0))) { moverr = (moverr+ 1) % LOGF; }
    if (!(PINB & (1<<3))) { moverr = 10; }
    if (!(PINB & (1<<4))) { moverr = 11; }  // <-- PB4 for exit

    switch(moverr) {
    case HOURF:
        if(!(PINB & (1<<1))){ hour = (hour + 1) % 24; }
        if(!(PINB & (1<<2))){ hour = (hour == 0) ? 23 : hour - 1; }
        LCD_moveCursor(0,6); LCD_displayString("  ");
        _delay_ms(150);
        LCD_moveCursor(0,6);
        if(hour < 10){ LCD_displayCharacter('0'); }
        LCD_intgerToString(hour);
        _delay_ms(150);
        break;

    case MINUTEF:
        if(!(PINB & (1<<1))){ min = (min + 1) % 60; }
        if(!(PINB & (1<<2))){ min = (min == 0) ? 59 : min - 1; }
        LCD_moveCursor(0,9); LCD_displayString("  ");
        _delay_ms(150);
        LCD_moveCursor(0,9);
        if(min < 10){ LCD_displayCharacter('0'); }
        LCD_intgerToString(min);
        _delay_ms(150);
        break;

    case SECONDF:
        if(!(PINB & (1<<1))){ sec = (sec + 1) % 60; }
        if(!(PINB & (1<<2))){ sec = (sec == 0) ? 59 : sec - 1; }
        LCD_moveCursor(0,12); LCD_displayString("  ");
        _delay_ms(150);
        LCD_moveCursor(0,12);
        if(sec < 10){ LCD_displayCharacter('0'); }
        LCD_intgerToString(sec);
        _delay_ms(150);
        break;

    case 10:  // Done setting
        LCD_clearScreen();
        LCD_displayStringRowColumn(0, 1, "Set Completed.");
        _delay_ms(1000);
        LCD_clearScreen();
        moverr = HOURF;
        return 1;  // finished
        break;

    case 11:  // Exit back to menu
        LCD_clearScreen();
        moverr = HOURF;
        _delay_ms(500);
        return 2;  // exit to main menu
        break;
    }
    return 0; // still editing
}
void reset_countdown(void) {
	hour = 0;
	min = 0;
	sec = 0;
	countdown_done_flag = 0;
	intrupt = 0;
	Buzzer_off();
}

