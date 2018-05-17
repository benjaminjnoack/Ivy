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
	static uint8_t resetBuf[] = {0x06};
	static uint8_t configBuf[] = {0x01, 0x31, 0x0C};

	xTaskDepth = configMINIMAL_STACK_SIZE + 128;

	pca9685Queue = xQueueCreate(10, sizeof(motor_command_t));//TODO enough?

	I2C_1_transfer.slaveAddress = SWRST_ADDRESS;
	I2C_1_transfer.data = resetBuf;
	I2C_1_transfer.dataSize = sizeof(resetBuf);
	I2C_MasterTransferBlocking(I2C1, &I2C_1_transfer);

	I2C_1_transfer.slaveAddress = PCA9685_ADDRESS;
	I2C_1_transfer.data = configBuf;
	I2C_1_transfer.dataSize = sizeof(configBuf);
	I2C_MasterTransferBlocking(I2C1, &I2C_1_transfer);

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

	I2C_1_transfer.data = I2C_1_buffer;
	I2C_1_transfer.dataSize = sizeof(I2C_1_buffer);

	for (;;) {
		xQueueReceive(pca9685Queue, &command, portMAX_DELAY);

		rxBuffer[command.motor] = command.power;
/**
 * TODO
 * specify command register
 * ensure alignment with the correct LED registers
 * specify the directions of the motors (perhaps one time in the initialization)
 */
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
