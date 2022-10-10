/*
 * API_Measure.h
 *
 *  Created on: 8 oct. 2022
 *      Author: lucas
 */

#ifndef API_INC_API_MEASURE_H_
#define API_INC_API_MEASURE_H_

#include <stdint.h>
#include <stdbool.h>
#include "stdlib.h"
#include "MPU6500.h"

#define ACCEL_THRESHOLD		0x1FFF //Accelerometer threshold
#define MBUFFER				10 //Measurements buffer size
#define FULL_SCALE			0xFFFF //Full scale value for tests

typedef bool bool_t;

typedef enum
{
	MEAS_OK,
	MEAS_ERROR

} Meas_Error_t;

enum
{
	NOT_MOVED,
	MOVED
};

uint8_t API_Measure_Init();
bool_t API_Measure_GetStatus();


#endif /* API_INC_API_MEASURE_H_ */
