
/*
 * -----------------------------------------------------------------------------------------------------------------------
 * --------------------------------------------- Mohamed_Magdy_Task ------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------------------------
 */

#ifndef SERVICE_SERVICE_H_
#define SERVICE_SERVICE_H_
#include<avr/io.h>
#include"../HAL/lcd.h"

#define CLOCK PB0
#define Alarm PB1
#define StopWatch PB2
#define CD  PB3
#define BACK_Exit PB4
/*
 *  AS we take a challenge to make our clock with only 5 buttons  and to make the code readable so we gonna make
 *  more than 1 define for the same pin
 */
#define display PB0
#define set     PB1
#define edit    PB2
#define tog    PB3
// زراير ال set حاليا احنا محتاجين زرار يتحرك علي الelements اللي عندي و بعدين يشوف هيعمل increment ولا decrement
#define movec PB0
#define inc   PB1
#define dec   PB2
#define ok    PB3
typedef enum {
	HOURF,
	MINUTEF,
	SECONDF,
	DAYF,
	MONTHF,
	YEARF,

	LOGF,
} TimeField;


//UI MODE

void welcome(void);
void select_mode(void);
void select_buttons(void);
uint8 Exit_mode(void);
void button_init(void);
// CLOCK MODE
// display mode
void clock_mode_display(void);
void clock_display(void);
void date_display(void);
void clock_1(void);
void update(void);
void mode_12_display(void);
void set_2(void);
void mode_12_hour(void);
void temp_display(void);
// set mode
void set_1st_diplay_void(void);
uint8 move(void);
void ince (void);
void dece (void);


#endif /* SERVICE_SERVICE_H_ */
