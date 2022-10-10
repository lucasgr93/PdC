/*
 * API_Measure.c
 *
 *  Created on: 8 oct. 2022
 *      Author: lucas
 */


#include "API_Measure.h"

/*Movement status*/
static uint8_t status;

/*Measurements buffers*/
static uint32_t accelX[MBUFFER];
static uint32_t accelY[MBUFFER];
static uint32_t accelZ[MBUFFER];

/*Last average values*/
static uint32_t avgX;
static uint32_t avgY;
static uint32_t avgZ;

/*Past average values*/
static uint32_t oldValueX;
static uint32_t oldValueY;
static uint32_t oldValueZ;

/*Private function prototypes*/
static void API_Measure_GetValues();
static void API_Measure_GetAverage();
static bool_t API_Measure_Evaluate();


/**
 * @brief  Initialize measuring module
 * @param  None
 * @retval Error code
 */
uint8_t API_Measure_Init()
{
	status = 0;
	memset(accelX, 0, sizeof(accelX));
	memset(accelY, 0, sizeof(accelY));
	memset(accelZ, 0, sizeof(accelZ));
	avgX = 0; avgY = 0; avgZ = 0;
	oldValueX = 0; oldValueY = 0; oldValueZ = 0;
	if(MPU6500_Init() != MEAS_OK) return MEAS_ERROR;
	return MEAS_OK;
}

/**
 * @brief  Tells whether the device has moved or not
 * @param  None
 * @retval True: Motion detected
 */
bool_t API_Measure_GetStatus()
{
	oldValueX = avgX;
	oldValueZ = avgY;
	oldValueY = avgZ;
	API_Measure_GetValues();
	API_Measure_GetAverage();
	return API_Measure_Evaluate();
}

/**
 * @brief  Get measurements from MPU6500 accelerometer
 * @param  None
 * @retval None
 */
static void API_Measure_GetValues()
{
	for(int i=0; i<MBUFFER; i++)
	{
		accelX[i] = MPU6500_GetAccelX();
		accelY[i] = MPU6500_GetAccelY();
		accelZ[i] = MPU6500_GetAccelZ();
	}
}

/**
 * @brief  Get average from saved measurements
 * @param  None
 * @retval None
 */
static void API_Measure_GetAverage()
{
	avgX = 0; avgY = 0; avgZ = 0;
	for(int i=0; i<MBUFFER; i++)
	{
		avgX += accelX[i];
		avgY += accelY[i];
		avgZ += accelZ[i];
	}
	avgX = avgX / MBUFFER;
	avgY = avgY / MBUFFER;
	avgZ = avgZ / MBUFFER;
}

/**
 * @brief  Evaluate if there has been a significant movement in the device
 * @param  None
 * @retval True: The device has moved
 */
static bool_t API_Measure_Evaluate()
{
	uint32_t diffX = abs(avgX - oldValueX);
	uint32_t diffY = abs(avgY - oldValueY);
	uint32_t diffZ = abs(avgZ - oldValueZ);

	if((diffX > ACCEL_THRESHOLD && diffX < 0x7FFF) ||
	   (diffY > ACCEL_THRESHOLD && diffY < 0x7FFF) ||
	   (diffZ > ACCEL_THRESHOLD && diffZ < 0x7FFF))
		{
			status = MOVED;
		}
	else status = NOT_MOVED;

	return status;
}



//
