/*
 * MPU6500.h
 *
 *  Created on: 7 oct. 2022
 *      Author: lucas
 */

#ifndef MPU6500_INC_MPU6500_H_
#define MPU6500_INC_MPU6500_H_

#include "MPU6500_port.h"

uint32_t MPU6500_Init();
uint32_t MPU6500_FactoryReset();
uint32_t MPU6500_WakeOnMotionMode();
uint32_t MPU6500_GetAccelX();
uint32_t MPU6500_GetAccelY();
uint32_t MPU6500_GetAccelZ();
uint32_t MPU6500_GetIntStatus();
uint32_t MPU6500_ConfigIntPin(uint8_t config);
uint32_t MPU6500_EnableInt(uint8_t config);
uint32_t MPU6500_DisableInt(uint8_t config);
uint32_t MPU6500_SetPowerMode(uint8_t config);
uint32_t MPU6500_SetEnabledDevices(uint8_t config);

#endif /* MPU6500_INC_MPU6500_H_ */
