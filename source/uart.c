/*
 * uart.c
 *
 *  Created on: Apr 16, 2018
 *      Author: ben
 */

#include "uart.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
uint8_t rxBuffer[UART_RX_BUFFER_LENGTH];
uint8_t *pRxBuffer;
QueueHandle_t xUartRxQueue;
xTaskHandle xUartRxTask;
uart_handle_t uartHandle;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void uartRxTask(void *pvParameters);

/*******************************************************************************
 * Code
 ******************************************************************************/

void uartInitialize(void) {
	uart_config_t config;

	pRxBuffer = rxBuffer;
	xUartRxQueue = xQueueCreate(UART_RX_BUFFER_LENGTH, sizeof(uint8_t));
	UART_GetDefaultConfig(&config);
	config.enableRx = true;
	config.enableRxRTS = true;

	UART_Init(UART1, &config, CLOCK_GetFreq(kCLOCK_CoreSysClk));

	UART_EnableInterrupts(UART1, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);
	NVIC_SetPriority(UART1_RX_TX_IRQn, 5);
	EnableIRQ(UART1_RX_TX_IRQn);

	if (xTaskCreate(uartRxTask, "UART RX", configMINIMAL_STACK_SIZE + 128, NULL, (configMAX_PRIORITIES + 1), &xUartRxTask) != pdPASS) {
		printf("UART RX creation failed!.\r\n");
		while (1)
			;
	}
}

/**
 * TODO
 * assemble them into frames
 * when the frame is complete, reset the buffer pointer
 */
void uartRxTask(void *pvParameters) {
	for (;;) {
		xQueueReceive(xUartRxQueue, pRxBuffer, portMAX_DELAY);
		printf("%d\r\n", *pRxBuffer);
		pRxBuffer++;//TODO wrap around
	}

	vTaskDelete(xUartRxTask);
}

void UART1_RX_TX_IRQHandler(void) {
	static uint8_t data[1];
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & UART_GetStatusFlags(UART1)) {
		data[0] = UART_ReadByte(UART1);
		xQueueSendFromISR(xUartRxQueue, data, &xHigherPriorityTaskWoken);
	}
}
