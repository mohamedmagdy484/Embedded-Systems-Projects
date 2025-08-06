/*
 * -----------------------------------------------------------------------------------------------------------------------
 * --------------------------------------------- Mohamed_Magdy_Task ------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------------------------
 */


#include<avr/io.h>
#include<util/delay.h>
#include"../Hal/lcd.h"
#include"../HAL/Ultrasonic.h"
#include"../HAL/POT.h"
#include"../MCAL/ADC.h"
#include"../MCAL/spi.h"
#include"../MCAL/TWI.h"
/*
 * sensing ecu
 */
const TWI_ConfigType TWI_config =
{
		0x02,
		400
};


int main(void){

	SREG|=(1<<7);
	SPI_initMaster();
	ADC_init();
	LCD_init();
	TWI_init(&TWI_config);
	Ultrasonic_init();
	uint16 distance=0;
	uint8 speed=0;
	uint16 last_read=999;
	uint16 speed_last=999;
	uint8 crash_flag=1;
	LCD_displayStringRowColumn(0, 0, "Task for CUERT");
	LCD_displayStringRowColumn(1, 0, "Mohamed  Magdy");
	_delay_ms(4000);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Mini Smart");
	LCD_displayStringRowColumn(1, 0,"Vehicle SIM.");
	_delay_ms(3000);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Distance=    cm");

	LCD_displayStringRowColumn(1, 0, "Speed % =    ");

	while(1){
		speed=POT_SPEED();




		TWI_start();

		if (TWI_getStatus() == 0x08)
		{
			TWI_writeByte((0x02 << 1));

			if (TWI_getStatus() == 0x18)
			{if(distance<=20){
				TWI_writeByte(0);
				_delay_ms(20);
				if(crash_flag==0){
					LCD_displayStringRowColumn(1, 0, "Motor OFF CRASH! ");
					crash_flag=1;
				}
			}
			else{
				TWI_writeByte(speed);
				_delay_ms(20);
				if(crash_flag==1){
					LCD_displayStringRowColumn(1, 0, "                ");
					_delay_ms(1);
					LCD_displayStringRowColumn(1, 0, "Speed % =    ");
					LCD_moveCursor(1, 10);
					LCD_intgerToString(speed);

					crash_flag = 0;
				}
				if(speed !=speed_last){
					LCD_moveCursor(1, 10);
					LCD_displayString("      ");
					LCD_moveCursor(1, 10);
					LCD_intgerToString(speed);
				}
				speed_last=speed;




			}
			}
		}

		TWI_stop();

		_delay_ms(10);

		distance=Ultrasonic_readDistance();

		if(distance!=last_read){
			LCD_moveCursor(0, 10);
			LCD_displayString("   ");
			LCD_moveCursor(0, 10);
			LCD_intgerToString(distance);
		}
		last_read=distance;

		_delay_ms(10);

		SPI_sendReceiveByte(distance);
		_delay_ms(10);










	}

}
