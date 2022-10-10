/*
 * MPU6500.c
 *
 *  Created on: 7 oct. 2022
 *      Author: lucas
 */

#include "MPU6500.h"


/**
 * @brief  Initialize MPU6500 driver module
 * @param  None
 * @retval Error code
 */
uint32_t MPU6500_Init()
{
	if(MPU6500_I2C_Init() != MPU6500_OK) return MPU6500_ERR;
	if(MPU6500_FactoryReset() != MPU6500_OK) return MPU6500_ERR;

	return MPU6500_OK;

}

/**
 * @brief  Performs a factory reset
 * @param  None
 * @retval Error code
 */
uint32_t MPU6500_FactoryReset()
{
	if(MPU6500_WriteRegister(PWR_MGMT_1, PWR_MGMT_1_DEVICE_RESET) != MPU6500_OK) return MPU6500_ERR;
	else return MPU6500_OK;
}

/**
 * @brief  Configures and enables Wake-On-Motion feature
 * @param  None
 * @retval Error code
 */
uint32_t MPU6500_WakeOnMotionMode()
{
	if(MPU6500_WriteRegister(PWR_MGMT_1, (PWR_MGMT_1_TEMP_DIS | PWR_MGMT_1_CLKSEL_AUTO)) != MPU6500_OK) return MPU6500_ERR;

	if(MPU6500_WriteRegister(PWR_MGMT_2, (PWR_MGMT_2_DIS_XG | PWR_MGMT_2_DIS_YG | PWR_MGMT_2_DIS_ZG)) != MPU6500_OK) return MPU6500_ERR;

	if(MPU6500_WriteRegister(ACCEL_CONFIG2, (ACCEL_CONFIG2_ACCEL_FCHOICE_B_0 | ACCEL_CONFIG2_A_DLPF_CFG_184)) != MPU6500_OK) return MPU6500_ERR;

	if(MPU6500_WriteRegister(INT_ENABLE, INT_ENABLE_WOM_EN) != MPU6500_OK) return MPU6500_ERR;

	if(MPU6500_WriteRegister(ACCEL_INTEL_CTRL, ACCEL_INTEL_CTRL_ACCEL_INTEL_EN | ACCEL_INTEL_CTRL_ACCEL_INTEL_MODE) != MPU6500_OK) return MPU6500_ERR;

	if(MPU6500_WriteRegister(WOM_THR, WOM_THR_MID) != MPU6500_OK) return MPU6500_ERR;

	if(MPU6500_WriteRegister(LP_ACCEL_ODR, LP_ACCEL_ODR_LPOSC_CLKSEL_0_98) != MPU6500_OK) return MPU6500_ERR;

	if(MPU6500_WriteRegister(PWR_MGMT_1, PWR_MGMT_1_CYCLE | PWR_MGMT_1_TEMP_DIS | PWR_MGMT_1_CLKSEL_AUTO) != MPU6500_OK) return MPU6500_ERR;

	if(MPU6500_WriteRegister(INT_PIN_CFG, INT_PIN_CFG_LATCH_INT_EN) != MPU6500_OK) return MPU6500_ERR;

	return MPU6500_OK;
}

/**
 * @brief  Gets accelerometer x-axis measurement
 * @param  None
 * @retval X-axis acceleration value
 */
uint32_t MPU6500_GetAccelX()
{
	return MPU6500_ReadRegister16(ACCEL_XOUT_H);
}

/**
 * @brief  Gets accelerometer y-axis measurement
 * @param  None
 * @retval Y-axis acceleration value
 */
uint32_t MPU6500_GetAccelY()
{
	return MPU6500_ReadRegister16(ACCEL_YOUT_H);
}

/**
 * @brief  Gets accelerometer z-axis measurement
 * @param  None
 * @retval Z-axis acceleration value
 */
uint32_t MPU6500_GetAccelZ()
{
	return MPU6500_ReadRegister16(ACCEL_ZOUT_H);
}

/**
 * @brief  Gets interrupt status register value
 * @param  None
 * @retval Interrupt status register value
 */
uint32_t MPU6500_GetIntStatus()
{
	return MPU6500_ReadRegister8(INT_STATUS);
}

/**
 * @brief  Configures interruption pin behaviour register
 * @param  None
 * @retval Error code
 */
uint32_t MPU6500_ConfigIntPin(uint8_t config)
{
	return MPU6500_WriteRegister(INT_PIN_CFG, config);
}

/**
 * @brief  Configures interruption enabling register
 * @param  None
 * @retval Error code
 */
uint32_t MPU6500_ConfigInt(uint8_t config)
{
	return MPU6500_WriteRegister(INT_ENABLE, config);
}

/**
 * @brief  Configures power mode register
 * @param  None
 * @retval Error code
 */
uint32_t MPU6500_SetPowerMode(uint8_t config)
{
	return MPU6500_WriteRegister(PWR_MGMT_1, config);
}

/**
 * @brief  Configures enabled peripherals register
 * @param  None
 * @retval Error code
 */
uint32_t MPU6500_SetEnabledDevices(uint8_t config)
{
	return MPU6500_WriteRegister(PWR_MGMT_2, config);
}
