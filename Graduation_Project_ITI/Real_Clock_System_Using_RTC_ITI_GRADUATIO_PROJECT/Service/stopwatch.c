/*
 * stopwatch.c
 *
 *  Created on: Aug 1, 2025
 *      Author: SIGMA
 */

#include<avr/io.h>
#include"stopwatch.h"
#include<util/delay.h>
#include"../HAL/rtc.h"
#include"../hal/buzzer.h"
#include"../HAL/lcd.h"
uint8 sec0 = 0, sec1 = 0;
uint8 min0 = 0, min1 = 0;
uint8  hour0 = 0, hour1 = 0;
volatile uint8  stopwatchs=0;
volatile uint8  stopwatchf=0;
volatile uint8  stopwatchss=0;
volatile uint8 buzzer_enable=0;
volatile uint8 awlmara=0;
/*timer _count up des
 * في الاول احنا هنخش علي الثواني لو لقينا ان الجزء الاول بتاع اول ثانيه نعمله بري انكريمينت لو لقينا انه معداش 10 يبقي خلاص تمام زود طيب لو لقينا انه عدي يبقي صفر المكان ده و تباعا
 * علشان العمليه تبقي سلسله اكتير لازم نمسكها من الاخر للاول فبالتالي لما اجي ازود او اقلل يبقي عامل حسابي ان كل الشروط تتحدث مع بعض فهنعمل if ladder ا
 * اللي هي ببسطاه تمام هعمل زياده للثواني و بعدين هتشيك علي كل حاجه تانيعه جايه بس و يفضلو يزيدو و يقلو سوا
 * و نفس الشيء او نفس الطريقه هتستخدم في ال count down
 *
 */
void Timer_countUp(void) {
	if (++sec0 > 9) {
		sec0 = 0;
		if (++sec1 > 5) {
			sec1 = 0;
			if (++min0 > 9) {
				min0 = 0;
				if (++min1 > 5) {
					min1 = 0;
					if (++hour0 > 9 || (hour1 == 2 && hour0 > 3)) {
						hour0 = 0;
						if (++hour1 > 2) {
							hour1 = 0;
						}
					}
				}
			}
		}
	}
	if(sec0 == 1)
	awlmara=1;

}
void display_stopwatch_before(void){
	LCD_displayStringRowColumn(0,3," 00:00:00");
	LCD_displayStringRowColumn(1,0,"Start Stop Reset");

}
void count_up_display(void){
	LCD_moveCursor(0,4);
	LCD_intgerToString(hour1);
	LCD_intgerToString(hour0);
	LCD_displayString(":");
	LCD_intgerToString(min1);
	LCD_intgerToString(min0);
	LCD_displayString(":");
	LCD_intgerToString(sec1);
	LCD_intgerToString(sec0);

}
void reset_values_before_and_after_exit(void){
	sec0 = 0, sec1 = 0;
	min0 = 0, min1 = 0;
	hour0 = 0, hour1 = 0;
}

