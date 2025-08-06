
   /*standard libraries*/
#include "avr/io.h"
#include <avr/interrupt.h>
#include<util/delay.h>
#include"../Common/common_macros.h"

       /*MCAL*/
#include "../MCAL/adc.h"

       /*HAL*/

#include "../HAL/LED.h"
#include "../HAL/lcd.h"
#include "../HAL/lm35_sensor.h"
#include "../HAL/ldr.h"
#include "../HAL/DC_motor.h"
#include "../HAL/flamesensor.h"
#include "../HAL/buzzer.h"

           /*the application */


        //=== LIGHT FUNCTION===//
void set_light(uint8 light){
	if(light<15){
		LED_on(LED_RED);
		LED_on(LED_GREEN);
		LED_on(LED_BLUE);

	}
	else if(light>15&&light<51){
		LED_on(LED_RED);
		LED_on(LED_GREEN);
		LED_off(LED_BLUE);
	}
	else if(light>=51&&light<=70){
		LED_on(LED_RED);
		LED_off(LED_BLUE);
		LED_off(LED_GREEN);


	}

	else{   LED_off(LED_RED);
		    LED_off(LED_BLUE);
	     	LED_off(LED_GREEN);

	}

}

//fan global variable//
uint8 lastFanSpeed = 255;





int main(void){
	ADC_init();
	DcMotor_Init();
	Buzzer_init();
	FlameSensor_init();
	LCD_init();
	LEDS_init();
	   uint8 fire_alert_displayed = 0;
	   uint8 fanSpeed=0;
	while(1){



        //===  LDR CODE   === //
uint8 light = 100 - LDR_getLightIntensity();
     set_light(light);

        //=== Temperature ===//

     uint8 temp = LM35_getTemperature();


     if(temp < 25)
         fanSpeed = 0;
     else if(temp < 30)
         fanSpeed = 25;
     else if(temp < 35)
         fanSpeed = 50;
     else if(temp < 40)
         fanSpeed = 75;
     else
         fanSpeed = 100;





     //===FLAME SENSOR===//

       if(FlameSensor_getValue())
       {  if (fire_alert_displayed == 0){
    	   Buzzer_on();
    	   LCD_clearScreen();
    	   LCD_displayStringRowColumn(0, 0, "Critical alert!  ");
    	   LCD_displayStringRowColumn(1, 0, "7ARE2A  ");
    	   fire_alert_displayed = 1;
       }
           continue;
       }
       else
       {
           Buzzer_off();
           fire_alert_displayed = 0;
           //=== LCD DISPLAY CODE===//

           LCD_moveCursor(0, 0);
             if(fanSpeed == 0){
                 LCD_displayString("FAN is OFF     ");
               DcMotor_Rotate(STOP, 0);
             }
             else{
                 LCD_displayString("FAN is ON      ");
                 DcMotor_Rotate(CW, fanSpeed);
             }

             LCD_moveCursor(1, 0);
             LCD_displayString("Temp=");
             LCD_intgerToString(temp);
             LCD_displayString("C ");

             LCD_displayString("LDR=");
             LCD_intgerToString(light);
             LCD_displayString("%  ");
       }



	}












}
