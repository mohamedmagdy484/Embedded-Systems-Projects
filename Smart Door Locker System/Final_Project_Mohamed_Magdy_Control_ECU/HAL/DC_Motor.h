





#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "../COMMON/std_types.h"
#include"../mcal/pwm.h"

// === Configurable motor control pins ===
#define DC_MOTOR_PORT      PORTD
#define DC_MOTOR_DDR       DDRD
#define DC_MOTOR_IN1       PD6
#define DC_MOTOR_IN2       PD7

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
