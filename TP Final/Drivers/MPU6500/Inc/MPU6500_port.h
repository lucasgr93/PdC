/*
 * MPU6500_port.h
 *
 *  Created on: 7 oct. 2022
 *      Author: lucas
 */

#ifndef MPU6500_INC_MPU6500_PORT_H_
#define MPU6500_INC_MPU6500_PORT_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"

/*MPU6500 register address definitions*/

#define	CONFIG				0x1A /*7:N/A, 6:FIFO_MODE, [5-3]:EXT_SYNC_SET, [2-0]:DLPF_CFG*/
#define	GYRO_CONFIG			0x1B /*7:XG_ST, 6:YG_ST, 5:ZG_ST, [4-3]:GYRO_FS_SEL, 2:N/A, [1-0]:FCHOICE_B*/
#define	ACCEL_CONFIG		0x1C /*7:XA_ST, 6:YA_ST, 5:ZA_ST [4-3]:ACCEL_FS_SEL, [2-0]:N/A*/
#define	ACCEL_CONFIG2		0X1D /*[7-4]:N/A, 3:ACCEL_FCHOICE_B, [2-0]:A_DLPF_CFG*/
#define	LP_ACCEL_ODR		0x1E /*[7-4]:N/A, [3-0]:LPOSC_CLKSEL*/
#define	WOM_THR				0x1F /*[7-0]:WOM_THRESHOLD*/
#define	FIFO_EN				0x23 /*7:TEMP_FIFO_EN, 6:GYRO_XOUT, 5:GYRO_YOUT, 4:GYRO_ZOUT, 3:ACCEL, 2:SLV2, 1:SLV1, 0:SLV0*/
#define	INT_PIN_CFG			0x37 /*7:ACTL, 6:OPEN, 5:LATCH_INT_EN, 4:INT_ANYRD_2CLEAR, 3:ACTL_FSYNC, 2:FSYNC_INT_MODE_EN, 1:BYPASS_EN, 0:N/A*/
#define	INT_ENABLE			0x38 /*7:N/A, 6:WOM_EN, 5:N/A, 4:FIFO_OFLOW_EN, 3:FSYNC_INT_EN, 2:N/A, 1:N/A, 0:RAW_RDY_EN*/
#define	INT_STATUS			0x3A /*7:N/A, 6:WOM_INT, 5:N/A, 4:FIFO_OFLOW_INT, 3:FSYNC_INT_INT, 2:N/A, 1:DMP_INT, 0:RAW_RDY_INT*/
#define	ACCEL_XOUT_H		0x3B /*[15-8]:ACCEL_XOUT_H*/
#define	ACCEL_XOUT_L		0x3C /*[7-0]:ACCEL_XOUT_L*/
#define	ACCEL_YOUT_H		0x3D /*[15-8]:ACCEL_YOUT_H*/
#define	ACCEL_YOUT_L		0x3E /*[7-0]:ACCEL_YOUT_L*/
#define	ACCEL_ZOUT_H		0x3F /*[15-8]:ACCEL_ZOUT_H*/
#define	ACCEL_ZOUT_L		0x40 /*[7-0]:ACCEL_ZOUT_L*/
#define	ACCEL_INTEL_CTRL	0x69 /*7:ACCEL_INTEL_EN, 6:ACCEL_INTEL_MODE, [5-0]:N/A*/
#define USER_CTRL			0x6A /*7:DMP_EN, 6:FIFO_EN, 5:I2C_MST_EN, 4:I2C_MST_DIS, 3:DMP_RST, 2:FIFO_RST, 1:I2C_MST_RST, 0:SIG_COND_RST*/
#define	PWR_MGMT_1			0x6B /*7:DEVICE_RESET, 6:SLEEP, 5:CYCLE, 4:GYRO_STANDBY, 3:TEMP_DIS, [2-0]:CLKSEL*/
#define	PWR_MGMT_2			0x6C /*[7-6]:N/A, 5:DIS_XA, 4:DIS_YA, 3:DIS_ZA, 2:DIS_XG, 1:DIS_YG, 0:DIS_ZG*/

#define HIGHEST_REGISTER	0x7E

#define MPU6500_MASK		0xFF

/*General configuration register bits definitions*/

#define	CONFIG_DEFAULT					0x00
#define CONFIG_FIFO_MODE				0x40
#define CONFIG_EXT_SYNC_SET_ACCEL_ZOUT	0x38
#define CONFIG_EXT_SYNC_SET_ACCEL_YOUT	0x30
#define CONFIG_EXT_SYNC_SET_ACCEL_XOUT	0x28
#define CONFIG_EXT_SYNC_SET_GYRO_ZOUT	0x20
#define CONFIG_EXT_SYNC_SET_GYRO_YOUT	0x18
#define CONFIG_EXT_SYNC_SET_GYRO_XOUT	0x10
#define CONFIG_EXT_SYNC_SET_TEMP		0x08
#define CONFIG_EXT_SYNC_SET_DIS_ALL		0x00
#define CONFIG_DLPF_CFG_3600			0x07
#define CONFIG_DLPF_CFG_5				0x06
#define CONFIG_DLPF_CFG_10				0x05
#define CONFIG_DLPF_CFG_20				0x04
#define CONFIG_DLPF_CFG_41				0x03
#define CONFIG_DLPF_CFG_92				0x02
#define CONFIG_DLPF_CFG_184				0x01
#define CONFIG_DLPF_CFG_250				0x00


/*Gyroscope configuration register bits definitions*/

#define GYRO_CONFIG_XG_ST				0x80
#define GYRO_CONFIG_YG_ST				0x40
#define GYRO_CONFIG_ZG_ST				0x20
#define GYRO_CONFIG_GYRO_FS_SEL_2000	0x18
#define GYRO_CONFIG_GYRO_FS_SEL_1000	0x10
#define GYRO_CONFIG_GYRO_FS_SEL_500		0x08
#define GYRO_CONFIG_GYRO_FS_SEL_250		0x00
#define GYRO_CONFIG_FCHOICE_B_8800		0x03
#define GYRO_CONFIG_FCHOICE_B_3600		0x02
#define GYRO_CONFIG_FCHOICE_B_ON		0x00 /*See CONFIG_DLPF_CFG configuration*/

/*Accelerometer configuration 1 register bits definitions*/

#define	ACCEL_CONFIG_XA_ST				0x80
#define	ACCEL_CONFIG_YA_ST				0x40
#define	ACCEL_CONFIG_ZA_ST				0x20
#define	ACCEL_CONFIG_ACCEL_FS_SEL_16G	0x18
#define	ACCEL_CONFIG_ACCEL_FS_SEL_8G	0x10
#define	ACCEL_CONFIG_ACCEL_FS_SEL_4G	0x08
#define	ACCEL_CONFIG_ACCEL_FS_SEL_2G	0x00

/*Accelerometer configuration 2 register bits definitions*/

#define	ACCEL_CONFIG2_ACCEL_FCHOICE_B_1	0x08
#define	ACCEL_CONFIG2_ACCEL_FCHOICE_B_0	0x00
#define	ACCEL_CONFIG2_A_DLPF_CFG_5		0x06
#define	ACCEL_CONFIG2_A_DLPF_CFG_10		0x05
#define	ACCEL_CONFIG2_A_DLPF_CFG_20		0x04
#define	ACCEL_CONFIG2_A_DLPF_CFG_41		0x03
#define	ACCEL_CONFIG2_A_DLPF_CFG_92		0x02
#define	ACCEL_CONFIG2_A_DLPF_CFG_184	0x01
#define	ACCEL_CONFIG2_A_DLPF_CFG_460	0x00

/*Low Power Accelerometer ODR control register bits definitions*/

#define	LP_ACCEL_ODR_LPOSC_CLKSEL_500	0x0B
#define	LP_ACCEL_ODR_LPOSC_CLKSEL_250	0x0A
#define	LP_ACCEL_ODR_LPOSC_CLKSEL_125	0x09
#define	LP_ACCEL_ODR_LPOSC_CLKSEL_62_5	0x08
#define	LP_ACCEL_ODR_LPOSC_CLKSEL_31_25	0x07
#define	LP_ACCEL_ODR_LPOSC_CLKSEL_15_63	0x06
#define	LP_ACCEL_ODR_LPOSC_CLKSEL_7_81	0x05
#define	LP_ACCEL_ODR_LPOSC_CLKSEL_3_91	0x04
#define	LP_ACCEL_ODR_LPOSC_CLKSEL_1_95	0x03
#define	LP_ACCEL_ODR_LPOSC_CLKSEL_0_98	0x02
#define	LP_ACCEL_ODR_LPOSC_CLKSEL_0_49	0x01
#define	LP_ACCEL_ODR_LPOSC_CLKSEL_0_24	0x00

/*Wake-on-motion threshold register bits definitions*/

#define	WOM_THR_HI						0xFF
#define	WOM_THR_MID						0x7F
#define	WOM_THR_LOW						0x01

/*FIFO Enable configuration register bits definitions*/

#define	FIFO_EN_TEMP_OUT				0x80
#define	FIFO_EN_GYRO_XOUT				0x40
#define	FIFO_EN_GYRO_YOUT				0x20
#define	FIFO_EN_GYRO_ZOUT				0x10
#define	FIFO_EN_ACCEL					0x08
#define	FIFO_EN_SLV_2					0x04
#define	FIFO_EN_SLV_1					0x02
#define	FIFO_EN_SLV_0					0x01
#define	FIFO_EN_NONE					0x00

/*Interruption pin configuration register bits definitions*/

#define INT_PIN_CFG_EN_ALL				0xFE
#define INT_PIN_CFG_ACTL				0x80
#define INT_PIN_CFG_OPEN				0x40
#define INT_PIN_CFG_LATCH_INT_EN		0x20
#define INT_PIN_CFG_INT_ANYRD_2CLEAR	0x10
#define INT_PIN_CFG_ACTL_FSYNC			0x08
#define INT_PIN_CFG_FSYNC_INT_MODE_EN	0x04
#define INT_PIN_CFG_BYPASS_EN			0x02
#define INT_PIN_CFG_DIS_ALL				0x00

/*Enable device interruption configuration register bits definitions*/

#define INT_ENABLE_ALL					0x59
#define INT_ENABLE_WOM_EN				0x40
#define INT_ENABLE_FIFO_OFLOW_EN		0x10
#define INT_ENABLE_FSYNC_INT_EN			0x08
#define INT_ENABLE_RAW_RDY_EN			0x01
#define INT_ENABLE_NONE					0x00

/*Interruptions status register bits definitions*/

#define	INT_STATUS_WOM_INT				0x40
#define	INT_STATUS_FIFO_OFLOW_INT		0x10
#define	INT_STATUS_FSYNC_INT_INT		0x08
#define	INT_STATUS_DMP_INT				0x02
#define	INT_STATUS_RAW_RDY_INT			0x01

/*Accelerometer intelligence configuration register bits definitions*/

#define	ACCEL_INTEL_CTRL_ACCEL_INTEL_EN		0x80
#define	ACCEL_INTEL_CTRL_ACCEL_INTEL_MODE	0x40
#define ACCEL_INTEL_CTRL_ACCEL_INTEL_DIS	0x00

/*User control register bits definitions*/

#define USER_CTRL_DMP_EN				0x80
#define USER_CTRL_FIFO_EN				0x40
#define USER_CTRL_I2C_MST_EN			0x20
#define USER_CTRL_I2C_MST_DIS			0x10
#define USER_CTRL_DMP_RST				0x08
#define USER_CTRL_FIFO_RST				0x04
#define USER_CTRL_I2C_MST_RST			0x02
#define USER_CTRL_SIG_COND_RST			0x01

/*Power mode configuration register bits definitions*/

#define	PWR_MGMT_1_DEVICE_RESET			0x80
#define	PWR_MGMT_1_SLEEP				0x40
#define	PWR_MGMT_1_CYCLE				0x20
#define	PWR_MGMT_1_GYRO_STANDBY			0x10
#define	PWR_MGMT_1_TEMP_DIS				0x08
#define	PWR_MGMT_1_CLKSEL_STOP			0x07
#define	PWR_MGMT_1_CLKSEL_20MHZ			0x06
#define	PWR_MGMT_1_CLKSEL_AUTO			0x05

/*Enabled devices configuration register bits definitions*/

#define	PWR_MGMT_2_DIS_ALL				0x3F
#define	PWR_MGMT_2_DIS_XA				0x20
#define	PWR_MGMT_2_DIS_YA				0x10
#define	PWR_MGMT_2_DIS_ZA				0x08
#define	PWR_MGMT_2_DIS_XG				0x04
#define	PWR_MGMT_2_DIS_YG				0x02
#define	PWR_MGMT_2_DIS_ZG				0x01
#define PWR_MGMT_2_EN_ALL				0x00

typedef bool bool_t;

typedef enum
{
	MPU6500_OK	=	0x00,
	MPU6500_ERR	= 	0x01

}MPU6500_StatusTypedef;

uint32_t MPU6500_I2C_Init();

uint32_t MPU6500_ReadRegister8(uint8_t regAddress);

uint32_t MPU6500_ReadRegister16(uint8_t regAddress);

uint32_t MPU6500_WriteRegister(uint8_t regAddress, uint8_t config);

#endif /* MPU6500_INC_MPU6500_PORT_H_ */
