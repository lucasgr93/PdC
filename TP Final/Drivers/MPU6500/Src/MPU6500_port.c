/*
 * MPU6500_port.c
 *
 *  Created on: 7 oct. 2022
 *      Author: lucas
 */

#include "MPU6500_port.h"

#define I2C_MASTER_ADDRESS	0x01
#define I2C_SLAVE_ADDRESS	0xD0
#define I2C_PORT			I2C1

#define BUFFERSIZE 2

/*HAL I2C structure*/
static I2C_HandleTypeDef I2cHandle;

/* Buffer used for transmission */
static uint8_t TxBuffer;

/* Buffer used for reception */
static uint8_t RxBuffer[2];

/**
 * @brief  Initialize I2C peripheral
 * @param  None
 * @retval Error code
 */
uint32_t MPU6500_I2C_Init()
{
	I2cHandle.Instance             = I2C1;
	I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
	I2cHandle.Init.ClockSpeed      = 400000;
	I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE_16_9;
	I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;
	I2cHandle.Init.OwnAddress1     = I2C_MASTER_ADDRESS;
	I2cHandle.Init.OwnAddress2     = 0xFE;

	uint32_t error = HAL_I2C_Init(&I2cHandle);
	return error;
}

/**
 * @brief  Performs a 16bits-long reading sequence
 * @param  regAddress: Target register
 * @retval Response value or error code
 */
uint32_t MPU6500_ReadRegister16(uint8_t regAddress)
{
	if(regAddress > HIGHEST_REGISTER) return MPU6500_ERR;
	memset(RxBuffer, 0, sizeof(RxBuffer));
	uint32_t data = 0;
	uint32_t error;
	error = HAL_I2C_Mem_Read(&I2cHandle, I2C_SLAVE_ADDRESS, regAddress, 1, RxBuffer, 2, 1000);
	if(error == MPU6500_OK)
	{
		error = HAL_I2C_GetError(&I2cHandle);
		if(error == HAL_I2C_ERROR_NONE)
		{
			data = RxBuffer[0]<<8;
			data += RxBuffer[1];
		}
		else
		{
			data = error;
		}
	}
	else data = error;

	return data;
}

/**
 * @brief  Performs an 8bits-long reading sequence
 * @param  regAddress: Target register
 * @retval Response value or error code
 */
uint32_t MPU6500_ReadRegister8(uint8_t regAddress)
{
	if(regAddress > HIGHEST_REGISTER) return MPU6500_ERR;
	memset(RxBuffer, 0, sizeof(RxBuffer));
	uint32_t data = 0;
	uint32_t error;
	error = HAL_I2C_Mem_Read(&I2cHandle, I2C_SLAVE_ADDRESS, regAddress, 1, RxBuffer, 1, 1000);
	if(error == MPU6500_OK)
	{
		error = HAL_I2C_GetError(&I2cHandle);
		if(error == HAL_I2C_ERROR_NONE)
		{
			data = RxBuffer[0];
		}
		else
		{
			data = error;
		}
	}
	else data = error;

	return data;
}

/**
 * @brief  Performs an 8bits-long writing sequence
 * @param  regAddress: Target register
 * @param  config: Configuration to be sent
 * @retval Error code
 */
uint32_t MPU6500_WriteRegister(uint8_t regAddress, uint8_t config)
{
	if(regAddress > HIGHEST_REGISTER) return MPU6500_ERR;
	TxBuffer = config;
	uint32_t error;
	error = HAL_I2C_Mem_Write(&I2cHandle, I2C_SLAVE_ADDRESS, regAddress, 1, &TxBuffer, 1, 1000);
	if(error == MPU6500_OK)
	{
		error = HAL_I2C_GetError(&I2cHandle);
	}

	return error;
}
