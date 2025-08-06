 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: Buzzer.c
 *
 * Author: Mohamed Magdy
 *
 *******************************************************************************/
#include "buzzer.h"
#include"../common/common_macros.h"
void Buzzer_init(void)
{
	SET_BIT(BUZZER_DDR,BUZZER_PIN);        // Set buzzer pin as output

    CLEAR_BIT(BUZZER_PORT,BUZZER_PIN);     // Turn buzzer off initially
}

void Buzzer_on(void)
{
	SET_BIT(BUZZER_PORT,BUZZER_PIN); // Set pin high
}

void Buzzer_off(void)
{
	CLEAR_BIT(BUZZER_PORT,BUZZER_PIN); // Set pin low
}
