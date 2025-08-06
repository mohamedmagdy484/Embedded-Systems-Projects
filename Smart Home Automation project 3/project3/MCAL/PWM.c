 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: PWM.C
 *
 * Description: Source file for the AVR GPIO driver
 *
 * Author: Mohamed Magdy
 *
 *******************************************************************************/

#include <avr/io.h>
#include "PWM.h"

void PWM_Timer0_Start(uint8 duty_cycle)
{
    // Set OC0 (PB3) as output
    DDRB |= (1 << PB3);

    // Set Fast PWM mode (WGM00 & WGM01 = 1), Non-inverting mode (COM01 = 1)
    TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS02) | (1 << CS00);
    // CS02 and CS00 -> Prescaler = 1024

    // Set duty cycle (0-100%)
    OCR0 = (uint8)((duty_cycle * 255UL) / 100);
}
