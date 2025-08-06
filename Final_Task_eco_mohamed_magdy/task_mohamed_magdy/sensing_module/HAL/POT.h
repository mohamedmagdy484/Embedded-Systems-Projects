/*
 * POT.h
 *
 *  Created on: Jul 23, 2025
 *      Author: SIGMA
 */

#ifndef HAL_POT_H_
#define HAL_POT_H_
#include "../COMMON/std_types.h"




/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define SENSOR_CHANNEL_ID         7
#define SENSOR_MAX_VOLT_VALUE     2.56
#define SENSOR_MAX_SPEED          410 // this value after trial and error as the pot didn't work propely in proteus
// so i could get the best value to limit the speed with 80km/hr

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


uint8 POT_SPEED(void);


#endif /* HAL_POT_H_ */
