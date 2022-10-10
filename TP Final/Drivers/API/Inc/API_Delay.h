/*
 * API_delay.h
 *
 *  Created on: 6 sep. 2022
 *  Author: Lucas
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#define MAX_DELAY	0xFFFF


typedef uint32_t tick_t;

typedef bool bool_t;

/**
 * Structure that contains the properties used to control the delay
 */
typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} Delay_t;

void delayInit( Delay_t * delay, tick_t duration );

bool_t delayRead( Delay_t * delay );

void delayWrite( Delay_t * delay, tick_t duration );


#endif /* API_INC_API_DELAY_H_ */
