/*
 * motor.c
 *
 *  Created on: May 13, 2018
 *      Author: ben
 */

#include "motor.h"

QueueHandle_t xMotorQueue;
TaskHandle_t xMotorTask;

void motorTask(void *pvParameters);

void motorInitialize(void) {
	BaseType_t xReturn;
	uint16_t xTaskDepth;

	xTaskDepth = configMINIMAL_STACK_SIZE + 128;

	xMotorQueue = xQueueCreate(10, MOTOR_COMM_SIZE);
	xReturn = xTaskCreate(motorTask, "Motor", xTaskDepth, NULL, (configMAX_PRIORITIES + 2), &xMotorTask);

	if (xReturn != pdPASS) {
		printf("Motor Task Creation Failed");
		while (1)
			;
	}
}

void motorTask(void *pvParameters) {
	static uint8_t command[MOTOR_COMM_SIZE];

	for (;;) {
		xQueueReceive(xMotorQueue, &command, portMAX_DELAY);

		switch (command[0]) {
		case AXIS_PITCH:
		case AXIS_ROLL:
		case AXIS_THRUST:
		case AXIS_YAW:
			break;
		}

		//TODO call xQueuePeekFromISR to see if the stop signal should be sent
	}
}

portBASE_TYPE motorSendToQueue(uint8_t *buf, TickType_t n) {
	return xQueueSendToBack(xMotorQueue, buf, n);
}
