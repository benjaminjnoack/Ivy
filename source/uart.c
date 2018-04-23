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

xTaskHandle xUartRxTask;
uart_handle_t g_uartHandle;
SemaphoreHandle_t xUartTxSemphr;
uart_transfer_t rxTransfer;
uint8_t rxBuffer[UART_BUFFER_LEN] = {0x00};
volatile bool rxOnGoing = false;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void uartRxTask(void *pvParameters);

/*******************************************************************************
 * Code
 ******************************************************************************/

void uartInitialize(void) {
	status_t status;
	uart_config_t config;

	UART_GetDefaultConfig(&config);
	config.enableRx = true;
	config.enableTx = true;
	//TODO enable CTS and RTS
	status = UART_Init(UART1, &config, CLOCK_GetFreq(kCLOCK_CoreSysClk));

	rxTransfer.data = rxBuffer;
	rxTransfer.dataSize = UART_BUFFER_LEN;

	NVIC_SetPriority(UART1_RX_TX_IRQn, 5);
//	UART_EnableInterrupts(UART1, kUART_RxDataRegFullInterruptEnable);

	UART_TransferCreateHandle(UART1, &g_uartHandle, UART_UserCallback, NULL);

	xUartTxSemphr = xSemaphoreCreateBinary();
//TODO stack size?
	if (xTaskCreate(uartRxTask, "UART RX", configMINIMAL_STACK_SIZE + 128, NULL, (configMAX_PRIORITIES + 1), &xUartRxTask) != pdPASS)
	{
		PRINTF("UART RX creation failed!.\r\n");
		while (1)
			;
	}
}

void uartRxTask(void *pvParameters) {
	static status_t rxStatus;

	for (;;) {
		rxStatus = UART_TransferReceiveNonBlocking(UART1, &g_uartHandle, &rxTransfer, NULL);
//		xSemaphoreTake(xUartTxSemphr, portMAX_DELAY);

		if (!rxOnGoing) {
			PRINTF("%s\r\n", rxTransfer.data);
			rxOnGoing = true;
		}
	}

	vTaskDelete(xUartRxTask);
}

void UART_UserCallback(UART_Type *base, uart_handle_t *handle, status_t status, void *userData) {
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	if (kStatus_UART_RxIdle == status) {
		rxOnGoing = false;
	} else {
		PRINTF("STAT: %d\n\n", status);
	}
}
