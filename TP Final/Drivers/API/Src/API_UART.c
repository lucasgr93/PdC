/*
 * API_UART.c
 *
 *  Created on: 27 sep. 2022
 *      Author: lucas
 */

#include "API_UART.h"

static UART_HandleTypeDef UartHandle;


/**
 * @brief  Initialize UART instance
 * @param  None
 * @retval True if initialization is correct or false if not
 */
bool API_UART_Init()
{
	/* UART configured as follows:
	      - Word Length = 8 Bits (7 data bit + 1 parity bit) :
		                  BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	      - Stop Bit    = One Stop bit
	      - Parity      = ODD parity
	      - BaudRate    = 9600 baud
	      - Hardware flow control disabled (RTS and CTS signals) */

	  UartHandle.Instance        = USARTx;

	  UartHandle.Init.BaudRate   = 9600;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle.Init.Parity     = UART_PARITY_ODD;
	  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode       = UART_MODE_TX_RX;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	  if(HAL_UART_Init(&UartHandle) == HAL_OK)
	  {
		  uint8_t welcomeMsg[] = "Inicialización correcta\n\rParámetros: Odd, 7, 1, No HwCtrl\r\n";
		  HAL_UART_Transmit(&UartHandle, welcomeMsg, sizeof(welcomeMsg), txTimeout);
		  return true;
	  }
	  else return false;
}

/**
 * @brief  Sends an entire string
 * @param  pstring: pointer to the string to be sent
 * @retval None
 */
void API_UART_SendString(uint8_t * pstring)
{
	if(pstring != NULL)
	{
		HAL_UART_Transmit(&UartHandle, pstring, strlen((const char*) pstring), txTimeout);
	}
	return;
}

/**
 * @brief  Main program
 * @param  pstring: pointer to the string to be sent
 * @param  size: amount of characters to be sent
 * @retval None
 */
void API_UART_SendStringSize(uint8_t * pstring, uint16_t size)
{
	if(pstring != NULL)
	{
		HAL_UART_Transmit(&UartHandle, pstring, size, txTimeout);
	}
	return;
}

/**
 * @brief  Main program
 * @param  pstring: pointer to the string to be sent
 * @param  size: amount of characters to be received
 * @retval None
 */
void API_UART_ReceiveStringSize(uint8_t * pstring, uint16_t size)
{
	if(pstring != NULL)
	{
		uint16_t* charsReceived = 0;
		HAL_UARTEx_ReceiveToIdle(&UartHandle, pstring, size, charsReceived, txTimeout);
	}
}
