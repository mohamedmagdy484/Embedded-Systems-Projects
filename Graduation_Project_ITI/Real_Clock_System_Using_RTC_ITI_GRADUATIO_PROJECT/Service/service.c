
/*
 * -----------------------------------------------------------------------------------------------------------------------
 * --------------------------------------------- Mohamed_Magdy_Task ------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------------------------
 */


#include<avr/io.h>
#include"service.h"
#include<util/delay.h>
#include"../HAL/rtc.h"
#include"../hal/buzzer.h"
extern uint8 mode;
TimeField mover=HOURF;
static uint8 hour=0;
static uint8 min=0;
static uint8 sec=0;
static uint8 day=0;
static uint8 month=0;
static uint8 year=0;
uint8 temp;
uint8 last_read=255;

void select_mode(void){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,2,"Select Mode");
	_delay_ms(1500);
	LCD_clearScreen();

	LCD_displayStringRowColumn(0,0,"1-Clock");
	LCD_displayStringRowColumn(0,8,"2-Alarm");
	LCD_displayStringRowColumn(1,0,"3-StopWatch");
	LCD_displayStringRowColumn(1,12,"4-CD");

}
void select_buttons(void){

	// clock mode
	if(!(PINB & (1<<CLOCK))){
		mode=1;
	}
	// alarm
	if(!(PINB & (1<<Alarm))){
		mode=2;
	}
	// stopwatch
	if(!(PINB & (1<<StopWatch))){
		mode=3;
	}
	//CD
	if(!(PINB & (1<<CD))){
		mode=4;
	}

}


uint8 Exit_mode(void){
	if(!(PINB & (1<<BACK_Exit))){
		_delay_ms(50);
		if(!(PINB & (1<<BACK_Exit))){
			return 1;

		}

	}
	return 0;


}
void clock_mode_display(void){

	LCD_displayStringRowColumn(0,0,"1-DISPLAY ");
	LCD_displayStringRowColumn(1,0,"2-SET");
	LCD_displayStringRowColumn(1,7,"3_12-Hr ");



}
void clock_display(void){
	LCD_displayStringRowColumn(0,0,"Time: ");
	LCD_moveCursor(0,6);

	if(RTC_getHour() < 10){
		LCD_displayCharacter('0');
		LCD_intgerToString(RTC_getHour());
	}
	else{
		LCD_intgerToString(RTC_getHour());


	}
	LCD_displayString(":");

	if(RTC_getMinute() < 10){
		LCD_displayCharacter('0');
		LCD_intgerToString(RTC_getMinute());
	}
	else{
		LCD_intgerToString(RTC_getMinute());


	}
	LCD_displayString(":");

	if(RTC_getSecond() < 10){
		LCD_displayCharacter('0');
		LCD_intgerToString(RTC_getSecond());
	}
	else{
		LCD_intgerToString(RTC_getSecond());
	}

}
void date_display(void){



	LCD_displayStringRowColumn(1,0,"Date: ");
	LCD_moveCursor(1,6);
	if(RTC_getDay() < 10){
		LCD_displayCharacter('0');
		LCD_intgerToString(RTC_getDay());
	}
	else{
		LCD_intgerToString(RTC_getDay());
	}
	LCD_displayString("/");
	if(RTC_getMonth() < 10){
		LCD_displayCharacter('0');
		LCD_intgerToString(RTC_getMonth());
	}
	else{
		LCD_intgerToString(RTC_getMonth());
	}

	LCD_displayString("/");

	if(RTC_getYear() < 10){
		LCD_displayCharacter('0');
		LCD_intgerToString(RTC_getYear());
	}
	else{
		LCD_intgerToString(RTC_getYear());
	}
	LCD_displayStringRowColumn(1, 14, "  ");



}
void set_1st_diplay_void(void){
	LCD_displayStringRowColumn(0, 0, "Time: HH:MM:SS");
	LCD_displayStringRowColumn(1, 0, "Date: DD/MM/YY  ");
}

uint8 move(void){
	if (!(PINB & (1<<0))) {
		mover = (mover+ 1) % LOGF;
	}
	if(!(PINB & (1<<3))){
		mover=10;
	}
	switch(mover){
	case HOURF:

		if(!(PINB & (1<<1))){
			hour++;
			if(hour > 23){
				hour = 0;
			}
		}
		if(!(PINB & (1<<2))){
			if(hour == 0){
				hour = 23;
			}
			else {
				hour--;
			}
		}
		LCD_moveCursor(0,6);
		LCD_displayString("  ");

		_delay_ms(150);

		LCD_moveCursor(0,6);
		if(hour < 10){
			LCD_displayCharacter('0');
		}

		LCD_intgerToString(hour);
		_delay_ms(150);
		break;
	case MINUTEF:
		if(!(PINB & (1<<1))){
			min++;
			if(min > 59){
				min = 0;
			}
		}
		if(!(PINB & (1<<2))){
			if(min == 0){
				min = 59;
			}
			else {
				min--;
			}
		}
		LCD_moveCursor(0, 9);    // مكان الدقيقة
		LCD_displayString("  ");
		_delay_ms(150);
		LCD_moveCursor(0, 9);
		if(min < 10){
			LCD_displayCharacter('0');

		}
		LCD_intgerToString(min);
		_delay_ms(150);


		break;
	case SECONDF:
		if(!(PINB & (1<<1))){
			sec++;
			if(sec > 59){
				sec = 0;
			}
		}
		if(!(PINB & (1<<2))){
			if(sec == 0){
				sec = 59;
			}
			else {
				sec--;
			}
		}
		LCD_moveCursor(0, 12);   // مكان الثانية
		LCD_displayString("  ");
		_delay_ms(150);
		LCD_moveCursor(0, 12);
		if(sec < 10){
			LCD_displayCharacter('0');

		}
		LCD_intgerToString(sec);
		_delay_ms(150);
		break;
	case DAYF:
		if(!(PINB & (1<<1))){
			day++;
			if(day > 31){
				day = 1;
			}
		}
		if(!(PINB & (1<<2))){
			if(day > 1){
				day--;
			}
			else {
				day = 31;
			}
		}
		LCD_moveCursor(1, 6);    // مكان اليوم
		LCD_displayString("  ");
		_delay_ms(150);
		LCD_moveCursor(1, 6);
		if(day < 10){
			LCD_displayCharacter('0');

		}
		LCD_intgerToString(day);
		_delay_ms(150);
		break;
	case MONTHF:
		if(!(PINB & (1<<1))){
			month++;
			if(month > 12){
				month = 1;
			}
		}
		if(!(PINB & (1<<2))){
			if(month > 1){
				month--;
			}
			else {
				month = 12;
			}
		}
		LCD_moveCursor(1, 9);    // مكان الشهر
		LCD_displayString("  ");
		_delay_ms(150);
		LCD_moveCursor(1, 9);
		if(month < 10){
			LCD_displayCharacter('0');

		}
		LCD_intgerToString(month);
		_delay_ms(150);
		break;
	case YEARF:
		if(!(PINB & (1<<1))){
			year++;
			if(year > 99){
				year = 0;
			}
		}
		if(!(PINB & (1<<2))){
			if(year == 0){
				year = 99;
			}
			else {
				year--;
			}
		}
		LCD_moveCursor(1, 12);   // مكان السنة
		LCD_displayString("  ");
		_delay_ms(150);
		LCD_moveCursor(1, 12);
		if(year < 10){
			LCD_displayCharacter('0');

		}
		LCD_intgerToString(year);
		_delay_ms(150);
		break;
	case 10:
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "Set Completed.");
		RTC_setTime(hour,min,sec);
		RTC_setDate(day,month,year);
		Buzzer_on();
		_delay_ms(500);
		Buzzer_off();
		_delay_ms(1500);
		LCD_clearScreen();
		mover = HOURF;
		return 1;
	}
	return 0;
}



void update (void){

	if (hour == 23 && min == 59 && sec == 59) {
		day++;

		uint8 daysInMonth;
		switch(month) {
		case 4: case 6: case 9: case 11:
			daysInMonth = 30;
			break;
		case 2:
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
				daysInMonth = 29;
			else
				daysInMonth = 28;
			break;
		default:
			daysInMonth = 31;
		}

		if (day > daysInMonth) {
			day = 1;
			month++;

			if (month > 12) {
				month = 1;
				year++;
			}
		}

		RTC_setDate(day, month, year);
	}
}

void mode_12_display(void){
	date_display();
	LCD_displayStringRowColumn(0,0,"Time: ");

	LCD_moveCursor(0,6);

	uint8 convert=RTC_getHour();
	if(convert == 0){
		LCD_intgerToString(12);
		LCD_displayStringRowColumn(0, 14, "Am");
	}
	else if(convert < 12){
		if(convert < 10){
			LCD_displayCharacter('0');
		}
		LCD_intgerToString(convert);
		LCD_displayStringRowColumn(0, 14, "Am");

	}
	else if(convert ==12){
		LCD_intgerToString(12);
		LCD_displayStringRowColumn(0, 14, "Pm");

	}
	else if(convert>12){
		convert=convert-12;
		if(convert<10){
			LCD_displayCharacter('0');

		}
		LCD_intgerToString(convert);
		LCD_displayStringRowColumn(0, 14, "Pm");

	}
	LCD_moveCursor(0,8);
	LCD_displayCharacter(':');


	LCD_moveCursor(0, 9);

	if(RTC_getMinute() < 10){
		LCD_displayCharacter('0');
		LCD_intgerToString(RTC_getMinute());
	}
	else{
		LCD_intgerToString(RTC_getMinute());


	}
	LCD_displayString(":");
	LCD_moveCursor(0, 12);
	if(RTC_getSecond() < 10){
		LCD_displayCharacter('0');
		LCD_intgerToString(RTC_getSecond());
	}
	else{
		LCD_intgerToString(RTC_getSecond());
	}


}


void button_init(void){
	DDRB=0X00;
	PORTB=0X3F;
	DDRA|=(1<<7);
	PORTA&=(1<<7);
	DDRB|=(1<<6);
	PORTB&=~(1<<6);

}




