/*
 * API_FSM.c
 *
 *  Created on: 13 sep. 2022
 *      Author: lucas
 */

#include "API_FSM.h"


static FSM_State_t FSM_State;
static Delay_t Meas_Delay;
static Delay_t Alive_Delay;
static bool_t motionDetected;

/**
 * @brief  Initializes FSM
 * @param  None
 * @retval Error code
 */
uint8_t API_FSM_init()
{
	delayInit(&Meas_Delay, MEAS_PERIOD);
	delayInit(&Alive_Delay, ALIVE_PERIOD);
	if(!API_UART_Init()) return FSM_ERROR;
	if(API_Measure_Init() != MEAS_OK) return FSM_ERROR;
	FSM_State = STAND_BY;
	motionDetected = false;
	return FSM_OK;
}

/**
 * @brief  Updates FSM
 * @param  None
 * @retval Error code
 */
uint8_t API_FSM_update()
{
	uint8_t error = FSM_OK;
	switch(FSM_State)
	{
		case STAND_BY:
		{
			if(motionDetected)
			{
				motionDetected = false;
				FSM_State = ALARM;
			}
			else if(delayRead(&Meas_Delay))
			{
				FSM_State = MEASURING;
			}
			else if(delayRead(&Alive_Delay))
			{
				FSM_State = ALIVE;
			}
			break;
		}
		case MEASURING:
		{
			if(API_Measure_GetStatus() == MOVED)
			{
				motionDetected = true;
				FSM_State = STAND_BY;
			}
			else FSM_State = STAND_BY;
			break;
		}
		case ALARM:
		{
			API_UART_SendString((uint8_t*)"ALARM: MOTION DETECTED\r\n\r\n");
			FSM_State = STAND_BY;
			break;
		}
		case ALIVE:
		{
			API_UART_SendString((uint8_t*)"I'M ALIVE. EVERYTHING OK\r\n\r\n");
			FSM_State = STAND_BY;
			break;
		}
		default:
		{
			error = FSM_ERROR;
			break;
		}
	}
	return error;

}
