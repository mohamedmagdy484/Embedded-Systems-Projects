/*===============================================================================================================
 * ---------------------------------------- Graduation Project ITI ----------------------------------------------
 * ==============================================================================================================
 *
 * ===============================================================================================================
 * --------------------------------------------- User Interface  -------------------------------------------------
 * ==============================================================================================================
 *
 * ===============================================================================================================
 * ------------------------------------------------- Author Magdy  ----------------------------------------------
 * ==============================================================================================================
 *
 */







#include<avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include"../MCAL/timer1.h"
#include "../MCAL/twi.h"

#include "../HAL/rtc.h"
#include "../HAL/lcd.h"
#include"../HAL/buzzer.h"

#include"../service/service.h"
#include"../service/stopwatch.h"
#include"../service/countdown.h"
#include "../Service/Alarm.h"

uint8 mode=0;
extern volatile uint8 stopwatchs;
extern volatile uint8 stopwatchf;
extern volatile uint8  stopwatchss;
extern volatile uint8 buzzer_enable;
extern volatile uint8 awlmara;
// External variables from countdown.c
extern volatile uint8 hour, min, sec;
extern volatile uint8 countdown_done_flag;
extern uint8 sec0 , sec1 ;
uint8 hours,mins ;
volatile uint8 timer0_counter = 0;



int main(void){
	LCD_init();
	Buzzer_init();
	RTC_init();
	button_init();
	SREG|=(1<<7);


	while(1){

		select_mode();
		update();
		while(mode == 0)
		{
			Check_Alarm();
			select_buttons();
		}

		switch(mode){
		case 1:
			Check_Alarm();

			LCD_displayStringRowColumn(0,0,"   Clock Mode    ");
			LCD_displayStringRowColumn(1,0,"                ");
			_delay_ms(1500);
			LCD_clearScreen();
			clock_mode_display();
			while(1){
				//mode display
				Check_Alarm();

				if(!(PINB & (1<<display))){
					LCD_clearScreen();
					while(1){
						Check_Alarm();

						date_display();
						clock_display();
						if(!(PINB & (1<<BACK_Exit))){
							LCD_clearScreen();
							clock_mode_display();
							break;


						}

					}

				}
				if(!(PINB & (1<<set))){
					LCD_clearScreen();
					set_1st_diplay_void();
					_delay_ms(1000);
					while(1){
						Check_Alarm();

						if(move()){
							clock_mode_display();
							break;
						}
						if(!(PINB & (1<<BACK_Exit))){
							LCD_clearScreen();
							clock_mode_display();
							break;


						}

					}

				}
				//end of mode 2
				if(!(PINB & (1<<PB2))){
					LCD_clearScreen();
					_delay_ms(1000);
					while(1){
						Check_Alarm();

						mode_12_display();

						if(!(PINB & (1<<BACK_Exit))){
							LCD_clearScreen();
							clock_mode_display();
							break;


						}

					}

				}

				if(Exit_mode()){
					break;
				}
			}
			if (returnMainWindow == 1) {
				LCD_clearScreen();
				returnMainWindow = 0;
				mode = 0;
				break;
			}
			mode = 0;
			break;

			/*===================================================================================================================
			 *===================================================================================================================
			 *===================================================================================================================
			 *===================================================================================================================
			 *===================================================================================================================
			 */

		case 2:

			LCD_displayStringRowColumn(0, 0, "   Alarm Mode    ");
			LCD_displayStringRowColumn(1, 0, "                ");
			_delay_ms(500);
			get_time(23, 0);

			while (1) {

				while (mode == 0) {
					if(Exit_mode()){

						break;
					}
					select_buttons();
					Check_Alarm();

					if (returnMainWindow == 1) {
						mode = 0;
						returnMainWindow = 0;
						break;
					}
				}

				if (returnMainWindow == 1) break;

				switch (mode) {
				case 1:
					hoursModification = !hoursModification;
					mode = 0;
					break;

				case 2: // Increment
					if (hoursModification)
						Increment_decrementHours(INC);
					else
						Increment_decrementMins(INC);

					// مسح الجزء الخاص بـ HH:MM
					LCD_displayStringRowColumn(0, 11, "     ");

					// إعادة عرض الوقت بعد التعديل
					Show_time();

					_delay_ms(150);
					mode = 0;
					break;

				case 3: // Decrement
					if (hoursModification)
						Increment_decrementHours(DEC);
					else
						Increment_decrementMins(DEC);

					// مسح الجزء الخاص بـ HH:MM
					LCD_displayStringRowColumn(0, 11, "     ");

					// إعادة عرض الوقت بعد التعديل
					Show_time();

					_delay_ms(150);
					mode = 0;
					break;

				case 4:
					if (is_Stopped == 0) {
						Set_Alarm(&hours, &mins);
						mode = 5;
						returnMainWindow = 1;
					}
					is_Stopped = 1;
					break;
				}

				if (Exit_mode()) break;

				if (returnMainWindow == 1) {
					mode = 0;
					returnMainWindow = 0;
					break;
				}
			}
			mode = 0;
			break;

			/*==================================================================================================================
			 *===================================================================================================================
			 *===================================================================================================================
			 *===================================================================================================================
			 *===================================================================================================================
			 */






		case 3:
			Check_Alarm();

			Timer1_init();
			LCD_displayStringRowColumn(0,0,"    StopWatch    ");
			LCD_displayStringRowColumn(1,0,"                ");
			_delay_ms(1500);
			LCD_clearScreen();
			display_stopwatch_before();
			LCD_displayStringRowColumn(1, 0, "Start Stop Reset");

			reset_values_before_and_after_exit();
			stopwatchs=0;
			stopwatchf=0;
			stopwatchss=0;
			buzzer_enable=0;
			awlmara=0;
			PORTA&=~(1<<7);

			while(1){
				Check_Alarm();

				if(!(PINB & (1<<0))){
					stopwatchs=1;
					stopwatchf=1;
					stopwatchss = 0;
					TCCR1B |= (1 << CS12) | (1 << CS10);
				}
				if(stopwatchs ==1){
					count_up_display();
					stopwatchs=0;
				}
				if(!(PINB & (1<<1))){
					stopwatchss=1;
					stopwatchs=0;
					stopwatchf=0;

				}
				if(!(PINB & (1<<2))){
					display_stopwatch_before();
					reset_values_before_and_after_exit();
					stopwatchs=0;
					stopwatchf=0;
					stopwatchss=0;
				}
				if(!(PINB & (1<<3))){
					_delay_ms(20);
					if(!(PINB & (1<<3))){
						buzzer_enable^=1;

					}
				}

				if(buzzer_enable==1){
					PORTA|=(1<<7);
					if(sec0 == 0 && sec1 == 0 && awlmara==1){
						Buzzer_on();
						_delay_ms(10);
						Buzzer_off();
					}


				}
				else if(buzzer_enable ==0){
					PORTA&=~(1<<7);

				}


				if(Exit_mode()){
					PORTA&=~(1<<7);

					break;
				}
				if (returnMainWindow == 1) {
					mode = 0;
					returnMainWindow = 0;
				    LCD_clearScreen();

					break;
				}
			}
			mode = 0;
			break;
			/*==========================================================================================
			 * ---------------------------------- STOP WATCH DONE ---------------------------------------
			 * ==========================================================================================
			 */




		case 4:
			Check_Alarm();

			// ================= COUNTDOWN MODE ==================
			reset_countdown();
			LCD_displayStringRowColumn(0, 0, "   Count Down    ");
			LCD_displayStringRowColumn(1, 0, "                ");
			_delay_ms(1500);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Set : HH:MM:SS");
			uint8_t set_result = 0;

			while (!(set_result = move_countdown())){  // Wait until user confirms or exits
				Check_Alarm();
			}

			if (set_result == 2) {
				LCD_clearScreen();
				set_result = 0;
				mode = 0;
				break;
			}

			countdown_done_flag = 0;
			intrupt = 1;
			Timer2_init();

			while (1) {
				Check_Alarm();

				if (countdown_done_flag) {
					LCD_clearScreen();
					LCD_displayString("   Time's up!");
					while (PINB & (1 << 3));
					Buzzer_off();
					LCD_clearScreen();
					LCD_displayString("    STOPPED");
					_delay_ms(1500);
					break;
				} else {
					LCD_moveCursor(0, 4);
					if (hour < 10) LCD_displayCharacter('0');
					LCD_intgerToString(hour);
					LCD_displayCharacter(':');
					if (min < 10) LCD_displayCharacter('0');
					LCD_intgerToString(min);
					LCD_displayCharacter(':');
					if (sec < 10) LCD_displayCharacter('0');
					LCD_intgerToString(sec);
					_delay_ms(200);
				}

				if (Exit_mode()) {
					reset_countdown();
					TCCR2 = 0x00; // إيقاف Timer2 بشكل آمن

					break;
				}

			}
			if (returnMainWindow == 1) {
				LCD_clearScreen();
				returnMainWindow = 0;
				mode = 0;
				break;
			}

			mode = 0;
			break;


		default:
			break;



		}





	}
}

ISR(TIMER1_COMPA_vect) {
	if(stopwatchf == 1){
		Timer_countUp();
		stopwatchs=1;

	}
	if(stopwatchss == 1){
		stopwatchss=0;
		TCCR1B &= ~((1 << CS10) | (1 << CS12));

	}
}

