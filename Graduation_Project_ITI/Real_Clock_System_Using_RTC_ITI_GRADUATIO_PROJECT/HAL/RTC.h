/*
 * RTC.h
 *
 *  Created on: Jul 29, 2025
 *      Author: SIGMA
 */

#ifndef HAL_RTC_H_
#define HAL_RTC_H_
#include<avr/io.h>
#include"../common/std_types.h"

typedef enum{
	AM,
	PM,
}time;
void RTC_init(void);
void RTC_setTime(uint8 h, uint8 m, uint8 s);
void RTC_setDate(uint8 d, uint8 m, uint8 y);


uint8 RTC_getSecond(void);
uint8 RTC_getMinute(void);
uint8 RTC_getHour(void);
uint8 RTC_getDay(void);
uint8 RTC_getMonth(void);
uint8 RTC_getYear(void);

#endif /* HAL_RTC_H_ */
