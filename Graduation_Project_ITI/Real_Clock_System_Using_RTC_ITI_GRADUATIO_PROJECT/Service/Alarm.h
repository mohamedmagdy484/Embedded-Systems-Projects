/*
 * Alarm.h
 *
 *  Created on: Jul 30, 2025
 *      Author: DELL
 */

#ifndef ALARM_ALARM_H_
#define ALARM_ALARM_H_
#include "../COMMON/std_types.h"
#include <avr/io.h>
#include <util/delay.h>
#include"../HAL/rtc.h"
#include"../HAL/lcd.h"
#include "../MCAL/gpio.h"
#include"service.h"
extern uint8 alarm_flag ;
extern uint8 hoursModification ;
extern uint8 is_Stopped ;
extern uint8 is_snoozed ;
extern uint8 returnMainWindow ;






#define DEC 0
#define INC 1




void get_time(uint8 h,uint8 m);

void Set_Alarm(uint8* hours,uint8* mins);

void Show_time(void);

void Stop_Alarm(void);

void Increment_decrementHours(uint8 inc_dec);

void Increment_decrementMins(uint8 inc_dec);

void Check_Alarm();

void Alarm_reset(void);

#endif /* ALARM_ALARM_H_ */
