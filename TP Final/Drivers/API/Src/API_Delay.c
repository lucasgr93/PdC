/*
 * API_delay.c
 *
 *  Created on: 6 sep. 2022
 *      Author: lucas
 */



#include <API_Delay.h>


/**
 * @brief  Initialize Non-blocking delay structure
 * @param  delay: pointer to a defined delay structure
 * @param  duration: duration of the delay in ms
 * @retval None
 */
void delayInit( Delay_t * delay, tick_t duration)
{
	if(delay != NULL && duration < MAX_DELAY)
	{
		delay->duration = duration;
		delay->running = false;
		delay->startTime = 0;
		return;
	}
}

/**
 * @brief  Reads the current status of the delay timer
 * @param  delay: pointer to a defined delay structure
 * @retval True: delay elapsed
 */
bool_t delayRead( Delay_t * delay )
{
	bool_t elapsed = false;
	if(delay != NULL)
	{
		if(!delay->running)
		{
			delay->running = true;
			delay->startTime = HAL_GetTick();
			elapsed = false;
		}
		/*We have to verify if the delay start time is less than the current timer time
		 * in case an overflow occurs*/
		else if(delay->startTime + delay->duration <= HAL_GetTick() && delay->startTime < HAL_GetTick())
		{
			delay->startTime = HAL_GetTick();
			elapsed =  true;
		}
	}
	return elapsed;
}

/**
 * @brief  Overwrites the current delay duration
 * @param  delay: pointer to a defined delay structure
 * @param  duration: duration of the delay in ms
 * @retval None
 */
void delayWrite( Delay_t * delay, tick_t duration )
{
	if(delay != NULL)
	{
		delay->duration = duration;
	}

	return;
}
