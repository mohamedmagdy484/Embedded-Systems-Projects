/*======================================================================================================
 *---------------------------------------- Author : Mohamed Magdy  -------------------------------------
 *======================================================================================================
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned int sec0 = 0, sec1 = 0;
volatile unsigned int min0 = 0, min1 = 0;
volatile unsigned int hour0 = 0, hour1 = 0;

volatile unsigned char pause_flag = 0;
volatile unsigned char timer_mode_flag = 1;
volatile unsigned char ISR_countUp_flag = 0;
volatile unsigned char ISR_countDown_flag = 0;
volatile unsigned char countdown_done_flag = 0;

void show_segments(void) {

	PORTA = (1 << 0);
	PORTC = (PORTC & 0xF0) | (sec0 & 0x0F);
	_delay_ms(5);
	PORTA = 0;

	PORTA = (1 << 1);
	PORTC = (PORTC & 0xF0) | (sec1 & 0x0F);
	_delay_ms(5);
	PORTA = 0;

	PORTA = (1 << 2);
	PORTC = (PORTC & 0xF0) | (min0 & 0x0F);
	_delay_ms(5);
	PORTA = 0;

	PORTA = (1 << 3);
	PORTC = (PORTC & 0xF0) | (min1 & 0x0F);
	_delay_ms(5);
	PORTA = 0;

	PORTA = (1 << 4);
	PORTC = (PORTC & 0xF0) | (hour0 & 0x0F);
	_delay_ms(5);
	PORTA = 0;

	PORTA = (1 << 5);
	PORTC = (PORTC & 0xF0) | (hour1 & 0x0F);
	_delay_ms(5);
	PORTA = 0;
}

void Timer_countUp(void) {
	if (++sec0 > 9) {
		sec0 = 0;
		if (++sec1 > 5) {
			sec1 = 0;
			if (++min0 > 9) {
				min0 = 0;
				if (++min1 > 5) {
					min1 = 0;
					if (++hour0 > 9) {
						hour0 = 0;
						if (++hour1 > 5) {
							hour1 = 0;
						}
					}
				}
			}
		}
	}
}

void Timer_countDown(void) {
	if (countdown_done_flag) return;

	if (sec0 > 0) sec0--;
	else {
		if (sec1 > 0) {
			sec1--; sec0 = 9;
		} else {
			if (min0 > 0) {
				min0--; sec1 = 5; sec0 = 9;
			} else if (min1 > 0) {
				min1--; min0 = 9; sec1 = 5; sec0 = 9;
			} else if (hour0 > 0) {
				hour0--; min1 = 5; min0 = 9; sec1 = 5; sec0 = 9;
			} else if (hour1 > 0) {
				hour1--; hour0 = 9; min1 = 5; min0 = 9; sec1 = 5; sec0 = 9;
			} else {

				sec0 = sec1 = min0 = min1 = hour0 = hour1 = 0;
				countdown_done_flag = 1;
				PORTD |= (1 << PD0);
			}
		}
	}
}

void Timer1_init(void) {
	TCCR1A = (1 << FOC1A);
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS12) | (1 << CS10);
	ICR1 = 7813;
	TIMSK |= (1 << OCIE1A);
	TCNT1 = 0;
}



void INT0_reset_init(void) {
	GICR |= (1 << INT0);
	MCUCR |= (1 << ISC01);
}

ISR(INT0_vect) {
	sec0 = sec1 = min0 = min1 = hour0 = hour1 = 0;
	countdown_done_flag = 0;
	PORTD &= ~(1 << PD0);
}

void INT1_pause_init(void) {
	GICR |= (1 << INT1);
	MCUCR |= (1 << ISC11) | (1 << ISC10);
}

ISR(INT1_vect) {
	_delay_ms(30);
	if (PIND & (1 << PD3)) {
		TCCR1B &= ~((1 << CS10) | (1 << CS12));
		pause_flag = 1;
	}
	PORTD &= ~(1 << PD0);
}

void INT2_resume_init(void) {
	GICR |= (1 << INT2);
	MCUCSR &= ~(1 << ISC2);
}

ISR(INT2_vect) {
	pause_flag = 0;
	TCCR1B |= (1 << CS12) | (1 << CS10);
}

int main(void) {
	DDRC |= 0x0F; PORTC &= 0xF0;
	DDRA |= 0x3F; PORTA = 0;

	DDRB = 0x00; PORTB = 0xFF;
	DDRD &= ~((1 << PD2) | (1 << PD3));
	PORTD |= (1 << PD2);

	DDRD |= (1 << PD0) | (1 << PD4) | (1 << PD5);
	PORTD &= ~((1 << PD0) | (1 << PD4) | (1 << PD5));

	Timer1_init();
	INT0_reset_init();
	INT1_pause_init();
	INT2_resume_init();
	SREG |= (1 << 7);

	while (1) {
		show_segments();

		if (ISR_countUp_flag) {
			Timer_countUp();
			ISR_countUp_flag = 0;
		}
		if (ISR_countDown_flag) {
			Timer_countDown();
			ISR_countDown_flag = 0;
		}


		if (!(PINB & (1 << PB7)) && pause_flag) {
			timer_mode_flag ^= 1;
			countdown_done_flag = 0;
			while (!(PINB & (1 << PB7))) show_segments();
		}


		if (timer_mode_flag) {
			PORTD |= (1 << PD4); PORTD &= ~(1 << PD5);
		} else {
			PORTD |= (1 << PD5); PORTD &= ~(1 << PD4);
		}


		if (!(PINB & (1 << PB0)) && pause_flag) {
			if (hour0 > 0) hour0--;
			else if (hour1 > 0) { hour0 = 9; hour1--; }
			else { hour0 = 9; hour1 = 5; }
			while (!(PINB & (1 << PB0))) show_segments();
		}

		if (!(PINB & (1 << PB1)) && pause_flag) {
			if (hour0 < 9) hour0++;
			else if (hour1 < 5) { hour0 = 0; hour1++; }
			else { hour0 = hour1 = 0; }
			while (!(PINB & (1 << PB1))) show_segments();
		}

		if (!(PINB & (1 << PB3)) && pause_flag) {
			if (min0 > 0) min0--;
			else if (min1 > 0) { min0 = 9; min1--; }
			else { min0 = 9; min1 = 5; }
			while (!(PINB & (1 << PB3))) show_segments();
		}

		if (!(PINB & (1 << PB4)) && pause_flag) {
			if (min0 < 9) min0++;
			else if (min1 < 5) { min0 = 0; min1++; }
			else { min0 = min1 = 0; }
			while (!(PINB & (1 << PB4))) show_segments();
		}

		if (!(PINB & (1 << PB5)) && pause_flag) {
			if (sec0 > 0) sec0--;
			else if (sec1 > 0) { sec0 = 9; sec1--; }
			else { sec0 = 9; sec1 = 5; }
			while (!(PINB & (1 << PB5))) show_segments();
		}

		if (!(PINB & (1 << PB6)) && pause_flag) {
			if (sec0 < 9) sec0++;
			else if (sec1 < 5) { sec0 = 0; sec1++; }
			else { sec0 = sec1 = 0; }
			while (!(PINB & (1 << PB6))) show_segments();
		}
	}
}
