/*
 * -----------------------------------------------------------------------------------------------------------------------
 * --------------------------------------------- Mohamed_Magdy_Task ------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------------------------
 */


/*
 * control ecu
 */
#include<avr/io.h>
#include<util/delay.h>
#include"../MCAL/spi.h"
#include"../HAL/DC_Motor.h"
#include"../MCAL/twi.h"
#include"../HAL/buzzer.h"
#include"../HAL/servo.h"

const TWI_ConfigType TWI_config =
{
		0x02,
		400
};






int main(void){
	TWI_init(&TWI_config);
	SPI_initSlave();
	DcMotor_Init();
	LCD_init();
	Buzzer_init();
	servo_init();
	uint8 speed_r=0;
	uint8 distance_r=0;

	while(1){
		ControlECU_TWI_SlaveReceive(&speed_r);
		DcMotor_Rotate(CW, speed_r);
		LCD_intgerToString(speed_r);

		distance_r=SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
		if(distance_r<=20){
			DcMotor_Rotate(CW,0);
			Buzzer_tog();
			servo_set_angle(30);
			_delay_ms(1);
			servo_set_angle(180);



		}
		else{
			Buzzer_off();

			servo_set_angle(45);
			_delay_ms(1);

			servo_set_angle(0);
			_delay_ms(1);


		}









	}






}
