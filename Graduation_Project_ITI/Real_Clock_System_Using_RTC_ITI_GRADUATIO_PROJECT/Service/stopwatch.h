/*
 * stopwatch.h
 *
 *  Created on: Aug 1, 2025
 *      Author: SIGMA
 */

#ifndef SERVICE_STOPWATCH_H_
#define SERVICE_STOPWATCH_H_
#include<avr/io.h>
void display_stopwatch_before(void);
void Timer_countUp(void);
void count_up_display(void);
void reset_values_before_and_after_exit(void);
void stop_watch(void);

#endif /* SERVICE_STOPWATCH_H_ */

