/*
 * pca9685.c
 *
 *  Created on: May 7, 2018
 *      Author: ben
 */

#include "pca9685.h"

QueueHandle_t pca9685Queue;
static TaskHandle_t pca9685TaskHandle;

void pca9685Task(void *pvParameters);

void pca9685Initialize(void) {
	BaseType_t xReturn;
	uint16_t xTaskDepth;
	static const uint8_t resetBuf[] = {SWRST_ADDRESS, 0x06};
	static const uint8_t configBuf[] = {PCA9685_ADDRESS << 1, 0x01, 0x31, 0x0C};

	xTaskDepth = configMINIMAL_STACK_SIZE + 128;

	pca9685Queue = xQueueCreate(10, sizeof(motor_command_t));//TODO enough?

	I2C_DisableInterrupts(I2C1, kI2C_GlobalInterruptEnable);
	I2C_MasterStart(I2C1, SWRST_ADDRESS, kI2C_Write);
	I2C_MasterWriteBlocking(I2C1, resetBuf, sizeof(resetBuf), kI2C_TransferDefaultFlag);
	I2C_MasterStop(I2C1);
	I2C_MasterStart(I2C1, PCA9685_ADDRESS, kI2C_Write);
	I2C_MasterWriteBlocking(I2C1, configBuf, sizeof(configBuf), kI2C_TransferDefaultFlag);
	I2C_MasterStop(I2C1);
	I2C_EnableInterrupts(I2C1, kI2C_GlobalInterruptEnable);

	xReturn = xTaskCreate(pca9685Task, "PCA 9685 RX", xTaskDepth, NULL, (configMAX_PRIORITIES + 2), &pca9685TaskHandle);

	if (xReturn != pdPASS) {
		printf("PCA RX Task Creation Failed");
		while (1)
			;
	}
}


void pca9685Task(void *pvParameters) {
	static motor_command_t command;
	static uint8_t rxBuffer[I2C_1_BUFFER_SIZE] = {0x00};

	for (;;) {
		xQueueReceive(pca9685Queue, &command, portMAX_DELAY);

		rxBuffer[command.motor] = command.power;

		if (uxQueueMessagesWaiting(pca9685Queue) == 0) {
			memcpy(I2C_1_buffer, rxBuffer, I2C_1_BUFFER_SIZE);//TODO necessary?
			I2C_MasterTransferNonBlocking(I2C1, &I2C_1_handle, &I2C_1_transfer);
			ulTaskNotifyTake(pdTRUE, portMAX_DELAY);//TODO timeout?
		}
	}
}

void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData) {
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (status == kStatus_Success) {
        vTaskNotifyGiveFromISR(pca9685TaskHandle, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}
