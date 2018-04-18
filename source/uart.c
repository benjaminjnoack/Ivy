/*
 * uart.c
 *
 *  Created on: Apr 16, 2018
 *      Author: ben
 */

#include "uart.h"

uint8_t rxBuffer[UART_BUF_SIZE];
uint8_t txBuffer[UART_BUF_SIZE];
struct _uart_handle uartHandle;
uart_rtos_handle_t uartRtosHandle;

void uartRxTask(void *pvParameters);

void uartInitialize(void) {
	uart_rtos_config_t uartRtosConfig = {
			.base = UART1,
			.srcclk = CLOCK_GetFreq(kCLOCK_CoreSysClk),
			.baudrate = 9600U,
			.parity = kUART_ParityDisabled,
			.stopbits = kUART_OneStopBit,
			.buffer = txBuffer,
			.buffer_size = UART_BUF_SIZE
	};

	NVIC_SetPriority(UART1_RX_TX_IRQn, 4);

	//TODO check success
	UART_RTOS_Init(&uartRtosHandle, &uartHandle, &uartRtosConfig);

	xTaskCreate(uartRxTask, "UART RX", configMINIMAL_STACK_SIZE + 120, NULL, configMAX_PRIORITIES + 1, NULL);
}

void uartRxTask(void *pvParameters) {
	static int error;
	size_t n;

	do {
		error = UART_RTOS_Receive(&uartRtosHandle, rxBuffer, UART_BUF_SIZE, &n);
		if (n > 0) {
			printf("Received %s\n", rxBuffer);
		}
	} while (kStatus_Success == error);
}
