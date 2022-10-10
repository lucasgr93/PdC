/*
 * API_FSM.h
 *
 *  Created on: 13 sep. 2022
 *      Author: lucas
 */

#ifndef API_INC_API_FSM_H_
#define API_INC_API_FSM_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "API_Measure.h"
#include "API_UART.h"
#include "API_Delay.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#define MEAS_PERIOD 1000 //Period between measurings
#define ALIVE_PERIOD 10000 //"I'm alive" report period

typedef enum
{
	STAND_BY,
	MEASURING,
	ALARM,
	ALIVE

} FSM_State_t;

typedef enum
{
	FSM_OK,
	FSM_ERROR

} FSM_Error_t;

uint8_t API_FSM_init();
uint8_t API_FSM_update();


#endif /* API_INC_API_FSM_H_ */
