
 /******************************************************************************
 *
 * Module: DC_Motor
 *
 *
 *
 *
 *
 * Author: Mohamed Magdy
 *
 *******************************************************************************/
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "../COMMON/std_types.h"


// === Configurable motor control pins ===
#define DC_MOTOR_PORT      PORTB
#define DC_MOTOR_DDR       DDRB
#define DC_MOTOR_IN1       PB0
#define DC_MOTOR_IN2       PB1

// === PWM output pin ===
#define PWM_PORT           DDRB
#define PWM_PIN            PB3  // OC0

typedef enum {
	STOP,
	CW,
	A_CW
} DcMotor_State;

// === Functions ===
void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state, uint8 speed); // speed: 0 - 100%

#endif /* DC_MOTOR_H_ */
