/*
 * control.c
 *
 *  Created on: Jul 9, 2025
 *      Author: Mohamed Magdy
 */
#include<avr/io.h>
#include<util/delay.h>
#define F_CPU 8000000UL

#include<avr/interrupt.h>
//===============================
#include"../hal/buzzer.h"
#include"../hal/dc_motor.h"
#include"../hal/external_eeprom.h"
#include"../hal/pir.h"
//===============================
#include "../mcal/twi.h"
#include "../mcal/uart.h"
#include "../mcal/timer.h"
/*=====================================================================================================
 * ----------------------------------------------------------------------------------------------------
 * ====================================================================================================
 */
volatile uint16 g_timer2_overflow_count = 0;
#define pass_size 5



/*=====================================================================================================
 * ----------------------------------------------------------------------------------------------------
 * ====================================================================================================
 */

// select the  configuration of the UART //
const UART_ConfigType UART_Config={UART_8BIT_MODE,no_parity,UART_ONE_STOP_BIT,UART_BAUD_9600};


// select the configuration for the timer //
const Timer_ConfigType Timer_config = {
    .timer_InitialValue = 0,
    .timer_compare_MatchValue = 0,
    .timer_ID = Timer2,
    .timer_clock = F_CPU_1024,
    .timer_mode = NORMAL_MODE
};
/* I2C/TWI configurations struct */
 const TWI_ConfigType TWI_config =
{
    0b00000010,
    400
};

 /*=====================================================================================================
  * ----------------------------------------------------------------------------------------------------
  * ====================================================================================================
  */

void Timer2_OverflowCallback(void);
void create_pass(void);
void check_pass(void);



int main(void){
	PIR_init();
	Buzzer_init();
	DcMotor_Init();
	TWI_init(&TWI_config);
	UART_init(&UART_Config);
	sei();
	Timer_setCallBack(Timer2_OverflowCallback, Timer2);
/*=====================================================================================================
 * -----------------------------------------main loop--------------------------------------------------
* =====================================================================================================
 */
uint8 hmi_byte=0;
while(1){
	hmi_byte=UART_recieveByte();
switch(hmi_byte){

case 1:
create_pass();
break;
case 2:
	check_pass();
break;
case 3:
	 DcMotor_Rotate(CW, 100);

	       Timer_init(&Timer_config);
	       Timer_setCallBack(Timer2_OverflowCallback, Timer2);


	            g_timer2_overflow_count = 0;

	            while (g_timer2_overflow_count < 458){ /* 15 seconds */

	            }

	            Timer_deInit(Timer2);

	            g_timer2_overflow_count = 0;

	            DcMotor_Rotate(CW, 0);

	            if (PIR_getState() == LOGIC_HIGH)
	            {
	            	UART_sendByte(7); /* hna lw el pir asht8l sa3tha htb3t 7 w el motor stop l7d ma yb3t 8*/
	                while (PIR_getState() == LOGIC_HIGH);
	            }

	            UART_sendByte(8); /* hna hyb3yt 8 3lshan y2fl el babbb */
	            break;
case 4: /* Lock door */
    DcMotor_Rotate(A_CW, 100);

    Timer_init(&Timer_config);
    Timer_setCallBack(Timer2_OverflowCallback, Timer2);


    g_timer2_overflow_count = 0;

    while (g_timer2_overflow_count < 458); /*  15 seconds  */
    Timer_deInit(Timer2);

    g_timer2_overflow_count = 0;

    DcMotor_Rotate(A_CW, 0); /* lma hyb3t 8 sa3tha el pir hyb3t 4 3lshan y5osh el case diiii */

    UART_sendByte(9); /* hna hwa el mafrood kda 5ls  */

    break;

case 5: /* case el 3 marat */
    Timer_init(&Timer_config);
    Timer_setCallBack(Timer2_OverflowCallback, Timer2);


    g_timer2_overflow_count = 0;

    while (g_timer2_overflow_count < 1831) /* 60 seconds  */
    {
    	Buzzer_on();
    	_delay_ms(500);
    	Buzzer_off();
    	_delay_ms(500);

    }

    Buzzer_off();
    Timer_deInit(Timer2);
    UART_sendByte(9);

    break;
}
}
}

/*=====================================================================================================
 * ----------------------------------------------------------------------------------------------------
 * ====================================================================================================
 */
void create_pass(void){
uint8 pass1[pass_size];
uint8 pass2[pass_size];
uint8 match = 1;

for(int i=0;i<pass_size;i++){
	pass1[i]=UART_recieveByte();
}
for(int i=0;i<pass_size;i++){
	pass2[i]=UART_recieveByte();
}

for(int i=0;i<pass_size;i++)
{

if(pass1[i]!=pass2[i]) {
match=0;
	}

}
if(match==1){
	 for (uint8 i = 0; i < pass_size; i++)// lw 7asl w pass 1= pass2 sa3tha 5zno f eeprom
	        {
	            EEPROM_writeByte(0x0000 + i, pass1[i]);// searched
	            _delay_ms(10);
	        }
	  UART_sendByte(0);
}
else
{
	  UART_sendByte(1);

}
}
/*=====================================================================================================
 * ----------------------------------------------------------------------------------------------------
 * ====================================================================================================
 */
void check_pass(void){
uint8 pass_saved[pass_size];
uint8 new_pass[pass_size];
uint8 match=1;
for(int i=0;i<pass_size;i++){
	new_pass[i]=UART_recieveByte();
}
// hna anta 3mlt call ll pass ely f el eeprom
for(int i=0;i<pass_size;i++){
	EEPROM_readByte(0x0000 + i, &pass_saved[i]);
	 _delay_ms(10);
}
for(int i=0;i<pass_size;i++){
if (pass_saved[i]!=new_pass[i]){
	match=0;
}


}
if(match==1){
	  UART_sendByte(0);

}
else {
	  UART_sendByte(1);

}
}
/*=====================================================================================================
 * ----------------------------------------------------------------------------------------------------
 * ====================================================================================================
 */
void Timer2_OverflowCallback(void){
	g_timer2_overflow_count++;
}

