/*
 * Timer.c
 *
 *  Created on: Jul 7, 2025
 *      Author: SIGMA
 */
#include "avr/io.h" /* To use the Timer Registers */
#include"Timer.h"
#include "../common/common_macros.h" /* To use the macros like SET_BIT */
#include<avr/interrupt.h>



static volatile void (*g_callBackPtr[3])(void) = {NULL_PTR, NULL_PTR, NULL_PTR};


/*
▪ Description: Function to initialize the Timer driver
▪ Inputs: pointer to the configuration structure with type Timer_ConfigType.
▪ Return: None
*/
void Timer_init(const Timer_ConfigType * Config_Ptr)
{
    switch(Config_Ptr->timer_ID)
    {
    case Timer0:
        TCNT0 = (uint8) Config_Ptr->timer_InitialValue;

        if(Config_Ptr->timer_mode == COMPARE_MODE)
        {
            OCR0 = (uint8) Config_Ptr->timer_compare_MatchValue;
            SET_BIT(TIMSK, OCIE0);
            SET_BIT(TCCR0, FOC0);
            SET_BIT(TCCR0, WGM01);
            CLEAR_BIT(TCCR0, WGM00);
        }
        else if(Config_Ptr->timer_mode == NORMAL_MODE)
        {
            SET_BIT(TIMSK, TOIE0);
            SET_BIT(TCCR0, FOC0);
            CLEAR_BIT(TCCR0, WGM00);
            CLEAR_BIT(TCCR0, WGM01);
        }

        TCCR0 |= (Config_Ptr->timer_clock & 0x07); // Set prescaler
        break;

    case Timer1:
        TCNT1 = Config_Ptr->timer_InitialValue;

        if(Config_Ptr->timer_mode == COMPARE_MODE)
        {
            OCR1A = Config_Ptr->timer_compare_MatchValue;
            SET_BIT(TIMSK, OCIE1A);
            SET_BIT(TCCR1A, FOC1A);
            TCCR1B |= (1 << WGM12);   // CTC Mode
        }
        else if(Config_Ptr->timer_mode == NORMAL_MODE)
        {
            SET_BIT(TIMSK, TOIE1);
            SET_BIT(TCCR1A, FOC1A);
            CLEAR_BIT(TCCR1B, WGM12); // Normal mode
        }

        TCCR1B |= (Config_Ptr->timer_clock & 0x07);
        break;

    case Timer2:
        TCNT2 = (uint8) Config_Ptr->timer_InitialValue;

        if(Config_Ptr->timer_mode == COMPARE_MODE)
        {
            OCR2 = (uint8) Config_Ptr->timer_compare_MatchValue;
            SET_BIT(TIMSK, OCIE2);
            SET_BIT(TCCR2, FOC2);
            SET_BIT(TCCR2, WGM21);    // CTC mode
            CLEAR_BIT(TCCR2, WGM20);
        }
        else if(Config_Ptr->timer_mode == NORMAL_MODE)
        {
            SET_BIT(TIMSK, TOIE2);
            SET_BIT(TCCR2, FOC2);
            CLEAR_BIT(TCCR2, WGM20);  // Normal mode
            CLEAR_BIT(TCCR2, WGM21);
        }

        TCCR2 |= (Config_Ptr->timer_clock & 0x07);
        break;


    }
}

/*
▪ Description: Function to disable the Timer via Timer_ID.
▪ Inputs: Timer_ID
▪ Return: None
*/
void Timer_deInit(Timer_ID_Type timer_type)
{
    switch(timer_type)
    {
    case Timer0:
        TCCR0 = 0;
        TCNT0 = 0;
        OCR0  = 0;
        CLEAR_BIT(TIMSK, TOIE0);
        CLEAR_BIT(TIMSK, OCIE0);
        break;

    case Timer1:
        TCCR1A = 0;
        TCCR1B = 0;
        TCNT1  = 0;
        OCR1A  = 0;
        CLEAR_BIT(TIMSK, TOIE1);
        CLEAR_BIT(TIMSK, OCIE1A);
        break;

    case Timer2:
        TCCR2 = 0;
        TCNT2 = 0;
        OCR2  = 0;
        CLEAR_BIT(TIMSK, TOIE2);
        CLEAR_BIT(TIMSK, OCIE2);
        break;



    }

    // Reset the callback pointer
    if(timer_type >= Timer0 && timer_type <= Timer2)
    		{
    			g_callBackPtr[timer_type] = NULL_PTR;
    		}

}

/*
▪  Description: Function to set the Call Back function address to the required
Timer.
▪ Inputs: pointer to Call Back function and Timer Id you want to set The
Callback to it.
▪ Return: None
*/
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID ){
	if(a_timer_ID >= Timer0 && a_timer_ID <= Timer2)
		{
			g_callBackPtr[a_timer_ID] = a_ptr;
		}
}






/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr[Timer0] != NULL_PTR)
	{
		(*g_callBackPtr[Timer0])();
	}
}

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr[Timer0] != NULL_PTR)
	{
		(*g_callBackPtr[Timer0])();
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr[Timer1] != NULL_PTR)
	{
		(*g_callBackPtr[Timer1])();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr[Timer1] != NULL_PTR)
	{
		(*g_callBackPtr[Timer1])();
	}
}

ISR(TIMER2_OVF_vect)
{
	if(g_callBackPtr[Timer2] != NULL_PTR)
	{
		(*g_callBackPtr[Timer2])();
	}
}

ISR(TIMER2_COMP_vect)
{
	if(g_callBackPtr[Timer2] != NULL_PTR)
	{
		(*g_callBackPtr[Timer2])();
	}
}









































