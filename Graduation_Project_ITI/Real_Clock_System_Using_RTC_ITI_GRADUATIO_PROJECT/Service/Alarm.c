/*
 * Alarm.c
 *
 *  Created on: Jul 30, 2025
 *      Author: DELL
 */

#include "Alarm.h"

#include <util/delay.h>

extern uint8 mode;

uint8 hours, mins;
uint8 alarm_flag = 0;
uint8 hoursModification = 1;
uint8 is_Stopped = 0;
uint8 is_snoozed = 0;
uint8 returnMainWindow = 0;

void get_time(uint8 h, uint8 m){
	LCD_clearScreen();
	hours = h;
	mins = m;
	LCD_displayStringRowColumn(0, 0, "Alarm Set: ");
	LCD_displayStringRowColumn(0,11, "HH:MM");

	if (hours < 10)
		LCD_intgerToString(0);
	LCD_intgerToString(hours);
	LCD_displayCharacter(':');
	if (mins < 10)
		LCD_intgerToString(0);
	LCD_intgerToString(mins);
}

void Set_Alarm(uint8* h, uint8* m){
	*h = hours;
	*m = mins;

	uint8 rtc_hr = RTC_getHour();
	uint8 rtc_min = RTC_getMinute();
	_delay_ms(30);

	uint8 hours_difference, mins_difference;

	if (mins >= rtc_min) {
		mins_difference = mins - rtc_min;
	} else {
		mins_difference = (mins + 60) - rtc_min;
		hours = (hours == 0) ? 23 : hours - 1;
	}

	if (hours >= rtc_hr) {
		hours_difference = hours - rtc_hr;
	} else {
		hours_difference = (hours + 24) - rtc_hr;
	}

	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "It Will Ring in");

	LCD_moveCursor(1, 0);
	LCD_intgerToString(hours_difference);
	LCD_displayString(" Hrs");

	LCD_moveCursor(1, 8);
	LCD_intgerToString(mins_difference);
	LCD_displayString(" Min");

	_delay_ms(1000);
	LCD_clearScreen();
	returnMainWindow = 1;
}
void Increment_decrementHours(uint8 inc_dec){
	if (inc_dec == INC)
		hours = (hours == 23) ? 0 : hours + 1;
	else
		hours = (hours == 0) ? 23 : hours - 1;
}

void Increment_decrementMins(uint8 inc_dec){
	if (inc_dec == INC)
		mins = (mins == 59) ? 0 : mins + 1;
	else
		mins = (mins == 0) ? 59 : mins - 1;
}

void Show_time(){
	LCD_moveCursor(0, 11);

	if (hours < 10)
		LCD_displayCharacter('0');
	LCD_intgerToString(hours);
	LCD_displayCharacter(':');

	if (mins < 10)
		LCD_displayCharacter('0');
	LCD_intgerToString(mins);
}




void Check_Alarm(){
	uint8 hr = RTC_getHour();
	uint8 min = RTC_getMinute();
	_delay_ms(30);

	if (hr == hours && min == mins && is_Stopped == 1) {
		GPIO_writePin(PORTD_ID, PIN0_ID, 1); // Alarm ON

		while (1) {
			LCD_displayStringRowColumn(0, 0, "Alarm Ringing   ");
			LCD_displayStringRowColumn(1, 0, "      STOP      ");

			if (GPIO_readPin(PORTB_ID, PIN3_ID) == 0) {  // Stop pressed
				is_Stopped = 0;
				_delay_ms(30);
				LCD_clearScreen();
				returnMainWindow = 1;
				break;
			}
		}

		GPIO_writePin(PORTD_ID, PIN0_ID, 0); // Alarm OFF
		LCD_clearScreen();
		returnMainWindow = 1;
		Alarm_reset();
	}
}





void Alarm_reset(void){
	alarm_flag = 0;
	hoursModification = 1;
	is_Stopped = 0;
	is_snoozed = 0;
	returnMainWindow = 0;

}
