/*
 * Ultrasonic.c
 *
 *  Created on: Jun 25, 2025
 *      Author: Mohamed Magdy
 */
#include<avr/io.h>
#include"../Common/common_macros.h"
#include"../HAL/Ultrasonic.h"


  volatile uint8 g_edgeCount=0;
  volatile uint16 g_timeHigh=0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/* ▪ Description:
▪ Initialize the ICU driver as required.
▪ Set up the ICU callback function.
▪ Set the direction for the trigger pin as output through
the GPIO driver.
▪ Inputs: None.
▪ Return: None. */


void Ultrasonic_init(void){
	const ICU_ConfigType config={F_CPU_8,RAISING};
	ICU_init(&config);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
    GPIO_setupPinDirection(Ultrasonic_Trigger_PORT_ID,Ultrasonic_Trigger_PIN_ID ,PIN_OUTPUT);


}
/* ▪ Description:
▪ Send the trigger pulse to the ultrasonic sensor.
▪ Inputs: None.
▪ Return: None. */

void Ultrasonic_Trigger(void){
    GPIO_writePin(Ultrasonic_Trigger_PORT_ID,Ultrasonic_Trigger_PIN_ID,LOGIC_HIGH);
    _delay_us(10);
    GPIO_writePin(Ultrasonic_Trigger_PORT_ID,Ultrasonic_Trigger_PIN_ID,LOGIC_LOW);
}
/*▪ Description:
▪ Send the trigger pulse by using the Ultrasonic_Trigger
function.
▪ Start the measurement process via the ICU driver.
6
▪ Inputs: None.
▪ Return: The measured distance in centimeters.*/

uint16 Ultrasonic_readDistance(void){
	  uint16 distance=0;
	  g_edgeCount = 0;
    Ultrasonic_Trigger();
    _delay_ms(200);// 3lshan el polling msh sh8al f3mlt delay 3lshan el cpu load
    distance=(uint16)(g_timeHigh / 117.6);

    return (distance+1);
}



void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */		ICU_clearTimerValue();

		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = ICU_getInputCaptureValue();
		/* Detect rising edge */
		ICU_setEdgeDetectionType(RAISING);

	}

}















