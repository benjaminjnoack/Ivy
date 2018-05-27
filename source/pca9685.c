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
	uint8_t resetBuf[] = {SWRST_ADDRESS};
	uint8_t configBuf[] = {
			MODE1_ADDRESS,
			(MODE1_ALLCALL | MODE1_AI),
			(MODE2_OUTDRV | MODE2_OCH)
	};
	uint8_t initBuf[] = {
			//LED2_ON_L_ADDRESS
			0x0E,
			//LED 2
			0x00,
			0x00,
			0x00,
			FULL_OFF,
			//LED 3
			0x00,
			FULL_ON,
			0x00,
			0x00,
			//LED 4
			0x00,
			0x00,
			0x00,
			FULL_OFF,
			//LED 5
			0x00,
			FULL_ON,
			0x00,
			0x00,
			//LED 6
			0x00,
			0x00,
			0x00,
			FULL_OFF,
			//LED 7
			0x00,
			0x00,
			0x00,
			FULL_OFF,
			//LED 8
			0x00,
			0x00,
			0x00,
			FULL_OFF,
			//LED 9
			0x00,
			FULL_ON,
			0x00,
			0x00,
			//LED 10
			0x00,
			0x00,
			0x00,
			FULL_OFF,
			//LED 11
			0x00,
			FULL_ON,
			0x00,
			0x00,
			//LED 12
			0x00,
			0x00,
			0x00,
			FULL_OFF,
			//LED 13
			0x00,
			0x00,
			0x00,
			FULL_OFF
	};

	xTaskDepth = configMINIMAL_STACK_SIZE + 128;

	pca9685Queue = xQueueCreate(16, sizeof(motor_command_t));

	I2C_1_transfer.slaveAddress = ALL_CALL_ADDRESS;
	I2C_1_transfer.data = resetBuf;
	I2C_1_transfer.dataSize = sizeof(resetBuf);
	I2C_MasterTransferBlocking(I2C1, &I2C_1_transfer);

	I2C_1_transfer.slaveAddress = PCA9685_ADDRESS;
	I2C_1_transfer.data = configBuf;
	I2C_1_transfer.dataSize = sizeof(configBuf);
	I2C_MasterTransferBlocking(I2C1, &I2C_1_transfer);

	I2C_1_transfer.slaveAddress = PCA9685_ADDRESS;
	I2C_1_transfer.data = initBuf;
	I2C_1_transfer.dataSize = sizeof(initBuf);
	I2C_MasterTransferBlocking(I2C1, &I2C_1_transfer);

	xReturn = xTaskCreate(pca9685Task, "PCA 9685 RX", xTaskDepth, NULL, (configMAX_PRIORITIES + 2), &pca9685TaskHandle);

	if (xReturn != pdPASS) {
		printf("PCA RX Task Creation Failed");
		while (1)
			;
	}

	NVIC_SetPriority(I2C1_IRQn, 5);
}


void pca9685Task(void *pvParameters) {
	static motor_command_t command;
	static uint8_t txBuffer[I2C_1_BUFFER_SIZE] = {0x00};

	I2C_1_transfer.data = I2C_1_buffer;
	I2C_1_transfer.dataSize = sizeof(I2C_1_buffer);

	for (;;) {
		xQueueReceive(pca9685Queue, &command, portMAX_DELAY);

		switch (command.motor) {
		case MOTOR_ONE:
			txBuffer[0] = 0x26;
			break;
		case MOTOR_TWO:
			txBuffer[0] = 0x3A;
			break;
		case MOTOR_THREE:
			txBuffer[0] = 0x0E;
			break;
		case MOTOR_FOUR:
			txBuffer[0] = 0x22;
			break;
		}

		if (command.power == 0xFF) {
			txBuffer[1] = 0x00;
			txBuffer[2] = FULL_ON;
			txBuffer[3] = 0x00;
			txBuffer[4] = 0x00;
		} else  {
			txBuffer[1] = 0x00;
			txBuffer[2] = 0x00;

			if (command.power == 0x00) {
				txBuffer[3] = 0x00;
				txBuffer[4] = FULL_OFF;
			} else {
				txBuffer[3] = command.power << 4;
				txBuffer[4] = command.power >> 4;
			}
		}

		memcpy(I2C_1_buffer, txBuffer, I2C_1_BUFFER_SIZE);
		I2C_MasterTransferNonBlocking(I2C1, &I2C_1_handle, &I2C_1_transfer);
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);//TODO timeout?
	}
}

portBASE_TYPE receiveMotorCommand(motor_command_t *command, TickType_t n) {
	return xQueueSendToBack(pca9685Queue, command, n);
}

void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData) {
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (status == kStatus_Success) {
        vTaskNotifyGiveFromISR(pca9685TaskHandle, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}
