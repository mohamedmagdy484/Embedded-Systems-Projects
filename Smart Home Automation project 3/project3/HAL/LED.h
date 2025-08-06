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








#ifndef LED_H_
#define LED_H_

#include "../COMMON/std_types.h"
typedef enum {
    LED_RED,
    LED_GREEN,
    LED_BLUE
} LED_ID;
/* ==== User Configuration ==== */


#define RED_LED_PORT   PORTB
#define RED_LED_DDR    DDRB
#define RED_LED_PIN    PB5
#define RED_LED_LOGIC  POSITIVE_LOGIC


#define GREEN_LED_PORT   PORTB
#define GREEN_LED_DDR    DDRB
#define GREEN_LED_PIN    PB6
#define GREEN_LED_LOGIC  POSITIVE_LOGIC


#define BLUE_LED_PORT   PORTB
#define BLUE_LED_DDR    DDRB
#define BLUE_LED_PIN    PB7
#define BLUE_LED_LOGIC  POSITIVE_LOGIC


#define POSITIVE_LOGIC  0
#define NEGATIVE_LOGIC  1

void LEDS_init(void);
void LED_on(LED_ID);
void LED_off(LED_ID);


#endif /* LED_H_ */
