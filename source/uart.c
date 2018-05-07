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

void uartRxTask(void *pvParameters) {
	uint8_t rxBuffer[1];

	static uint8_t frameBuffer[UART_RX_BUFFER_LENGTH];
	static uint8_t *pFrameIndex = frameBuffer;
	static bool frameStarted = false;
	static uint8_t bytesReceived = 0;

	for (;;) {
		xQueueReceive(xUartRxQueue, rxBuffer, portMAX_DELAY);

		if (!frameStarted) {
			if (SOH == rxBuffer[0]) {
				frameStarted = true;
			}

			continue;
		}

		*pFrameIndex = *rxBuffer;
		pFrameIndex++;
		bytesReceived++;

		if (bytesReceived == 3) {
			uint8_t checksum;
			uint8_t i;

			for (i = 0, checksum = 0xFF; i < 2; i++) {
				checksum = checksum ^ frameBuffer[i];
			}

			if (checksum == frameBuffer[bytesReceived - 1]) {
				printf("OK\r\n");
			} else {
				GPIO_PortClear(BOARD_INITPINS_LED_GREEN_GPIO, 1 << BOARD_INITPINS_LED_GREEN_GPIO_PIN);
			}

			bytesReceived = 0;
			pFrameIndex = frameBuffer;
			frameStarted = false;
		}
	}
	GPIO_PortClear(BOARD_INITPINS_LED_RED_GPIO, 1 << BOARD_INITPINS_LED_RED_GPIO_PIN);
	vTaskDelete(xUartRxTask);
}

void UART1_RX_TX_IRQHandler(void) {
	static uint8_t data[1];
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & UART_GetStatusFlags(UART1)) {
		data[0] = UART1->D;
		xQueueSendFromISR(xUartRxQueue, data, &xHigherPriorityTaskWoken);
	}
}
