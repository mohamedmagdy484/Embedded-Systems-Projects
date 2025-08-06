#include<avr/io.h>
#include <avr/interrupt.h>
#include<util/delay.h>
#include"../HAL/Ultrasonic.h"
#include "../HAL/LED.h"
#include "../HAL/lcd.h"
#include "../HAL/buzzer.h"



// Function To blink the leds no more //
void Blinking(void){
	LED_on(LED_RED);
	LED_on(LED_GREEN);
	LED_on(LED_BLUE);
	Buzzer_on();
	_delay_ms(600);
	LED_off(LED_RED);
	LED_off(LED_GREEN);
	LED_off(LED_BLUE);
	Buzzer_off();

}



int main(void){
	SREG|=(1<<7);
	Buzzer_init();
	LCD_init();
	LEDS_init();
	Ultrasonic_init();
	uint16 distance=0;
	uint16 last_read=900;// 3lshan t5ly elrqm my3mlsh flick//
	uint16 alarm =900;// 3lshan elrqm f alarm //
	LCD_displayStringRowColumn(0, 0, "Distance=    cm");
while(1){


     distance=Ultrasonic_readDistance();

     //=== to make the distance displayed without flickering===//
     // last read then move cursor delete 3 5anat b3den move tany w display //
     // mtnsah w ant 5arg t5ly distance=last_read//




if(distance!=last_read){
     LCD_moveCursor(0, 10);
     LCD_displayString("   ");
     LCD_moveCursor(0, 10);
     LCD_intgerToString(distance);
     last_read=distance;



     //         ========Conditions=======         //


     // ==== NO ALARM Conditions ====//
     	if(distance>20){
          	LED_off(LED_RED);
     	    LED_off(LED_GREEN);
     	    LED_off(LED_BLUE);
     	    Buzzer_off();

     	}
     	else if((distance>=16)&&(distance<=20)){
     		LED_off(LED_GREEN);
     		LED_off(LED_BLUE);
     		LED_on(LED_RED);
     		Buzzer_off();

     	}
     	else if((distance>=11)&&(distance<=15)){
     		LED_on(LED_RED);
     		LED_on(LED_GREEN);
     		LED_off(LED_BLUE);
     		Buzzer_off();


     	}
     	else if((distance>=6)&&(distance<=10)){
     		LED_on(LED_RED);
     		LED_on(LED_GREEN);
     		LED_on(LED_BLUE);
     		Buzzer_off();
     	}


        // ====  ALARM Condition ====//

       else if(distance<=5){
    	    distance=Ultrasonic_readDistance();
       	   LCD_displayStringRowColumn(1, 0, "     STOP!!        ");

    	   while(distance<=5){
     	   Blinking();
     	    distance=Ultrasonic_readDistance();
     	   if(distance!=alarm){
     	        LCD_moveCursor(0, 10);
     	        LCD_displayString("   ");
     	        LCD_moveCursor(0, 10);
     	        LCD_intgerToString(distance);
     	        alarm=distance;
    	   }

     }
      	   LCD_displayStringRowColumn(1, 0, "              ");





}
}
}
}
