/*
 * Timer.h
 *
 *  Created on: Jul 7, 2025
 *      Author: SIGMA
 */

#ifndef MCAL_TIMER_H_
#define MCAL_TIMER_H_
#include "../common/std_types.h"
//choose which timer u want to use //
typedef enum
{
	Timer0=0,
	Timer1=1,
	Timer2=2
}Timer_ID_Type;
// choose the clock u want to use it in ur timer with a defined prescaler//
typedef enum
{
	NO_CLOCK,
	F_CPU_CLOCK,
	F_CPU_8,
	F_CPU_64,
	F_CPU_256,
	F_CPU_1024
} Timer_ClockType;
// choose the mode of the timer  to complete and raise a flag //
typedef enum
{
	NORMAL_MODE,
	COMPARE_MODE
} Timer_ModeType;



typedef struct
{
uint16 timer_InitialValue;
uint16 timer_compare_MatchValue;     /*it will be used in compare mode only*/
Timer_ID_Type  timer_ID;
Timer_ClockType timer_clock;
Timer_ModeType  timer_mode;
}Timer_ConfigType;






void Timer_init(const Timer_ConfigType * Config_Ptr);
/*
▪ Description: Function to initialize the Timer driver
▪ Inputs: pointer to the configuration structure with type Timer_ConfigType.
▪ Return: None
*/
 void Timer_deInit(Timer_ID_Type timer_type);
 /*
▪ Description: Function to disable the Timer via Timer_ID.
▪ Inputs: Timer_ID
▪ Return: None
*/
 void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID );
 /*
▪  Description: Function to set the Call Back function address to the required
Timer.
▪ Inputs: pointer to Call Back function and Timer Id you want to set The
Callback to it.
▪ Return: None
*/

































#endif /* MCAL_TIMER_H_ */
