
 /******************************************************************************
 *
 * Module: DC_Motor
 *
 *
 *
 *
 *
 * Author: Mohamed Magdy
 *
 *******************************************************************************/
#include <avr/io.h>
#include "DC_Motor.h"

void DcMotor_Init(void)
{
    // Set IN1 and IN2 as output
    DC_MOTOR_DDR |= (1 << DC_MOTOR_IN1) | (1 << DC_MOTOR_IN2);

    // Set PWM pin (OC0) as output
    PWM_PORT |= (1 << PWM_PIN);

    // Set Timer0 to Fast PWM mode, non-inverting
    TCCR0 = (1 << WGM00) | (1 << WGM01)   // Fast PWM Mode
           | (1 << COM01)                 // Non-Inverting Mode
           | (1 << CS02) | (1 << CS00);   // Prescaler = 1024

    // Stop motor initially
    DC_MOTOR_PORT &= ~((1 << DC_MOTOR_IN1) | (1 << DC_MOTOR_IN2));
    OCR0 = 0; // 0% duty cycle
}

void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{

    if (speed > 100) speed = 100;

    // Convert % to 8-bit PWM value (0-255)
    OCR0 = (uint8)((speed * 255) / 100);

    switch (state)
    {
        case CW:
            DC_MOTOR_PORT |= (1 << DC_MOTOR_IN1);
            DC_MOTOR_PORT &= ~(1 << DC_MOTOR_IN2);
            break;
        case A_CW:
            DC_MOTOR_PORT |= (1 << DC_MOTOR_IN2);
            DC_MOTOR_PORT &= ~(1 << DC_MOTOR_IN1);
            break;
        case STOP:
        default:
            DC_MOTOR_PORT &= ~((1 << DC_MOTOR_IN1) | (1 << DC_MOTOR_IN2));
            break;
    }
}
