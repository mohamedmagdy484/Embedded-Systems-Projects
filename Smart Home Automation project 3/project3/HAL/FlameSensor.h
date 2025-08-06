
 /******************************************************************************
 *
 * Module: Flame Sensor
 *
 *
 *
 *
 *
 * Author: Mohamed Magdy
 *
 *******************************************************************************/

#ifndef FLAME_SENSOR_H_
#define FLAME_SENSOR_H_
#include <avr/io.h>
#include "../COMMON/std_types.h"
// === Configuration Macros ===
#define FLAME_SENSOR_PORT    PORTC
#define FLAME_SENSOR_PIN_REG PINC
#define FLAME_SENSOR_DDR     DDRC
#define FLAME_SENSOR_PIN     PC2

void FlameSensor_init(void);
/* Initializes the flame sensor pin direction.*/
uint8 FlameSensor_getValue(void);
/* Reads the value from the flame sensor and returns it.*/

#endif /* FLAME_SENSOR_H_ */
