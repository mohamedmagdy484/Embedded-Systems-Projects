/*
 * App_HMI.c
 *
 *  Created on: Jul 7, 2025
 *      Author: Mohamed Magdy
 */

#include<avr/io.h>
#include<util/delay.h>
#define F_CPU 8000000UL
#include<avr/interrupt.h>
//=================================================
#include"../mcal/uart.h"
#include"../mcal/timer.h"
#include"../mcal/uart.h"
//=================================================
#include"../hal/lcd.h"
#include"../hal/keypad.h"
//=================================================

/*
------------------------------------------------------------------------------------------------------------
start the configurations for the  HMI uart and timer
i will choose timer0 as it is easy to use it (8-bit)

------------------------------------------------------------------------------------------------------------
*/
#define pass_size 5
#define Enter_Key '='
#define pass_true 1
#define pass_false 0

// select the  configuration of the UART //
const UART_ConfigType UART_Config={UART_8BIT_MODE,no_parity,UART_ONE_STOP_BIT,UART_BAUD_9600};

// select the configuration for the timer //
const Timer_ConfigType Timer_config={0,0,Timer0,F_CPU_1024,NORMAL_MODE};
//===========================================================================================================
volatile uint16 g_timer0_overflow_count = 0;
uint8 g_matched_passwords = 0;
/*===========================================================================================================
 * Function Prototype
 * ==========================================================================================================
 */
void Timer0_OverflowCallback(void);
void Enter_pass_send(uint8*);
void Create_pass(void);
uint8 pass_checker(void);
//===========================================================================================================


/*===========================================================================================================
 * ----------------------------------------------------------------------------------------------------------
 * UART SEND BYTE EXPLAINATIONS
 * 1--> 3lshan t3ml password
 * 2--> 3lshan t3ml check 3la el password ely ma3molh save
 * 3--> door byft7 w gwaha hyb3t 7agteen (7) or (8) 3la 7sb el pir
 * 4--> lma el control yb3t 8 el hmi hyrod 3leh b 4 3lshan y2fl el baaaab
 * 5--> el 3 m7awalay btooooo3 el pass
 * 7--> m3naha en el sensor sh8aaaaal
 * 8--> m3naha en el pir b2a off
 * 9-->3lshan y3ml polling 3leha l7d ama twsl 9 sa3tha yrg3 el system
 * -----------------------------------------------------------------------------------------------------------
 * ===========================================================================================================
 */








int main(void){
// initalize the harware and ecu
	UART_init(&UART_Config);
	Timer_init(&Timer_config);
	Timer_setCallBack(Timer0_OverflowCallback, 0);
	LCD_init();
    LCD_displayString(" Mohamed Magdy");
    LCD_moveCursor(1,1);
    LCD_displayString("thanks Edges");
    _delay_ms(5000);
    LCD_clearScreen();



	sei(); /* Enables global interrupts */
	uint8 select=0,sensor=0xFF;
			/* 3LASHN HWA BA5OD INPUT MSH OUTPUT*/
// hna atna lazm ykono el 2 pass zy b3d 3lshan tbd2 tsht8l
while(g_matched_passwords!=1){
	Create_pass();
}
/*===========================================================================================================
 * -------------------------------------------main loop------------------------------------------------------
 * ==========================================================================================================
 */


while(1){
	        LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "+ : Open Door");
			LCD_displayStringRowColumn(1, 0, "- : Change Pass");
  select=KEYPAD_getPressedKey();
switch(select){
/*===========================================================================================================
 *    -------------------------------------------DOOR------------------------------------------------------
 * ==========================================================================================================
 */

case'+':
	 if(pass_checker() == pass_true){
	        UART_sendByte(3);
	        LCD_clearScreen();
	        LCD_displayStringRowColumn(0,0,"DOOR Unlocking");
	        LCD_moveCursor(1,0);
	        LCD_displayString("Pls Wait...");

	        sensor = UART_recieveByte();

	        if(sensor == 7){
	            LCD_clearScreen();
	            LCD_displayString("Wait for people");
	            LCD_moveCursor(1,0);
	            LCD_displayString("Entering");
	            sensor = UART_recieveByte();
	        }

	        if(sensor == 8){
	            UART_sendByte(4);
	            LCD_clearScreen();
	            LCD_displayString("Door is locking");
	        }

	        while(UART_recieveByte() != 9);
	        LCD_clearScreen();
	        LCD_displayStringRowColumn(0,0,"Door locked!");
	        LCD_displayStringRowColumn(1,0,"Returning...");
	         _delay_ms(15000);// 3lshan el proteus w el timer
	    }
	    break;

/*===========================================================================================================
 * ------------------------------------------- CHANGE PASS -------------------------------------------------
 * ==========================================================================================================
 */
case'-':
	if(pass_checker()==pass_true){
		g_matched_passwords = 0;
		LCD_clearScreen();
		LCD_displayString("Change password");
		LCD_moveCursor(1,0);
		LCD_displayString("    Process");
	    _delay_ms(350);

	}
	while(g_matched_passwords != 1){
		Create_pass();
	}
	break;
}
}
}
/*----------------------------------------------------------------------------------------------------------------------
 * Function to enter a password and send it to the control ecu
 * ---------------------------------------------------------------------------------------------------------------------
 */
void Enter_pass_send(uint8*pass){
	uint8 i=0;
	while(i<pass_size){
		uint8 enterd_key = KEYPAD_getPressedKey();
if(enterd_key >= 0 && enterd_key <= 9){
	pass[i]=enterd_key;
	LCD_displayCharacter('*');
	 i++;
	 _delay_ms(300);// hna ana 3aml el delay dah 3lshan el keypad by3ml debounce f proteus by3ml exessive cpu load

}
_delay_ms(300);

	}
  while(KEYPAD_getPressedKey()!=Enter_Key){
	  _delay_ms(500);
  }

	for(int j=0;j<pass_size;j++){
		UART_sendByte(pass[j]);
	}

}



/*----------------------------------------------------------------------------------------------------------------------
 * function to create a password hd5l el pass b3deen hda5lo tany to verify kol dah f el CONTROL ECU lw kano s7 hy3ml send
 * ---------------------------------------------------------------------------------------------------------------------
 */
void Create_pass(void){
	uint8 pass1[pass_size];
	uint8 pass2[pass_size];
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"DOOR LOCKER SYS.");
	_delay_ms(1000);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Pls Enter Pass:");
	LCD_moveCursor(1,0);
	UART_sendByte(1);
	Enter_pass_send(pass1);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Pls Renter Pass:");
	LCD_moveCursor(1,0);
	LCD_displayString("same pass:");
	LCD_moveCursor(1,10);
	Enter_pass_send(pass2);
	if(UART_recieveByte() == 0){
		g_matched_passwords=1;
	}
	else{	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Pass Not Match");
	_delay_ms(500);
	LCD_displayStringRowColumn(1,0,"Try again");
	g_matched_passwords = 0;
	_delay_ms(350);


	}





}
/*=======================================================================================================================
 * el function dy b2a 3lshan t3ml verify ll pass ely anta md5lo for 1 2 and 3 times w b3den lw lsa 8lt t3ml wait 1 minute
 *=======================================================================================================================
 */
uint8 pass_checker(void){
uint8 pass_check[pass_size];// array ll pass ely ht3ml check 3leh fe el control ecu
uint8 incorrect_pass_counter=0,incorrect_flag=0;
incorrect_flag=1;// hna anta awl m7
while(incorrect_flag==1){// dy awl mra 3lshan td5l el pass
	    LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"Please Enter ");
		LCD_moveCursor(1,0);
		LCD_displayString("saved pass:");
		UART_sendByte(2);//
		Enter_pass_send(pass_check);
uint8 after_check=UART_recieveByte();// astna el rd mn el control ecu
if(after_check==0){// lw tl3o zy ba3d yb2a tmam
	incorrect_pass_counter=0;
	incorrect_flag=0;
	return pass_true;
}// hna zawd el counter l7d 3 w law wsl 3nd el mara el 3 sa3tha system locked

incorrect_pass_counter++;
LCD_clearScreen();
LCD_displayString("Incorrect pass");
_delay_ms(500);
if(incorrect_pass_counter==3){
    UART_sendByte(5);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"System Locked ");
	LCD_displayStringRowColumn(1,0,"Wait for 1 Min. ");
	while(UART_recieveByte()!=9);
	incorrect_pass_counter=0;
	incorrect_flag=0;
return pass_false;
}

}
return pass_false;
}

/*====================================================================================================================
 *-----------------------------------------End of the functions ------------------------------------------------------
 *====================================================================================================================
 */


void Timer0_OverflowCallback(void)
{
	g_timer0_overflow_count++;
}
