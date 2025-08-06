
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
#include "FlameSensor.h"
#include "Buzzer.h"
#include "../COMMON/std_types.h"

void FlameSensor_init(void)
{
    // Set the sensor pin as input
    FLAME_SENSOR_DDR &= ~(1 << FLAME_SENSOR_PIN);
}

uint8 FlameSensor_getValue(void)
{
    // Return the logic level from the sensor pin (0 or 1)
    return (FLAME_SENSOR_PIN_REG & (1 << FLAME_SENSOR_PIN)) ? LOGIC_HIGH : LOGIC_LOW;
}
