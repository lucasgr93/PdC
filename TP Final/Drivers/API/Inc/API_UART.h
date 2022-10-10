/*
 * API_UART.h
 *
 *  Created on: 27 sep. 2022
 *      Author: lucas
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h"	/* <- BSP include */

#define txTimeout 100 //Transmition timeout in ms
#define USARTx	USART3

bool API_UART_Init();
void API_UART_SendString(uint8_t * pstring);
void API_UART_SendStringSize(uint8_t * pstring, uint16_t size);
void API_UART_ReceiveStringSize(uint8_t * pstring, uint16_t size);


#endif /* API_INC_API_UART_H_ */
