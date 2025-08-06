
 /******************************************************************************
 *
 * Module: Led Driver
 *
 *
 *
 *
 *
 * Author: Mohamed Magdy
 *
 *******************************************************************************/



#include "LED.h"
#include "../COMMON/common_macros.h"
#include<avr/io.h>
#include"../MCAL/gpio.h"
void LEDS_init(void)
{
	   /* Red */
	    GPIO_setupPinDirection(RED_LED_PORT, RED_LED_PIN , PIN_OUTPUT);
	    LED_off(LED_RED);

	    /* Green */
	    GPIO_setupPinDirection(GREEN_LED_PORT, GREEN_LED_PIN, PIN_OUTPUT);
	    LED_off(LED_GREEN);

	    /* Blue */
	    GPIO_setupPinDirection(BLUE_LED_PORT, BLUE_LED_PIN, PIN_OUTPUT);
	    LED_off(LED_BLUE);
}


void LED_on(LED_ID id)
{  switch (id) {
case LED_RED:
    #if (RED_LED_LOGIC == POSITIVE_LOGIC)
        SET_BIT(RED_LED_PORT, RED_LED_PIN);
    #else
        CLEAR_BIT(RED_LED_PORT, RED_LED_PIN);
    #endif
    break;

case LED_GREEN:
    #if (GREEN_LED_LOGIC == POSITIVE_LOGIC)
        SET_BIT(GREEN_LED_PORT, GREEN_LED_PIN);
    #else
        CLEAR_BIT(GREEN_LED_PORT, GREEN_LED_PIN);
    #endif
    break;

case LED_BLUE:
    #if (BLUE_LED_LOGIC == POSITIVE_LOGIC)
        SET_BIT(BLUE_LED_PORT, BLUE_LED_PIN);
    #else
        CLEAR_BIT(BLUE_LED_PORT, BLUE_LED_PIN);
    #endif
    break;
}

}

void LED_off(LED_ID id)
{
    switch (id) {
        case LED_RED:
            #if (RED_LED_LOGIC == POSITIVE_LOGIC)
                CLEAR_BIT(RED_LED_PORT, RED_LED_PIN);
            #else
                SET_BIT(RED_LED_PORT, RED_LED_PIN);
            #endif
            break;

        case LED_GREEN:
            #if (GREEN_LED_LOGIC == POSITIVE_LOGIC)
                CLEAR_BIT(GREEN_LED_PORT, GREEN_LED_PIN);
            #else
                SET_BIT(GREEN_LED_PORT, GREEN_LED_PIN);
            #endif
            break;

        case LED_BLUE:
            #if (BLUE_LED_LOGIC == POSITIVE_LOGIC)
                CLEAR_BIT(BLUE_LED_PORT, BLUE_LED_PIN);
            #else
                SET_BIT(BLUE_LED_PORT, BLUE_LED_PIN);
            #endif
            break;
    }
}




