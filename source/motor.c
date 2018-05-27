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

	static motor_command_t motor1 = {.motor = MOTOR_ONE, .power = 0x00};
	static motor_command_t motor2 = {.motor = MOTOR_TWO, .power = 0x00};
	static motor_command_t motor3 = {.motor = MOTOR_THREE, .power = 0x00};
	static motor_command_t motor4 = {.motor = MOTOR_FOUR, .power = 0x00};

	for (;;) {
		xQueueReceive(xMotorQueue, &command, portMAX_DELAY);

		switch (command[0]) {
		case AXIS_PITCH:
		case AXIS_ROLL:
		case AXIS_YAW:
			break;
		case AXIS_THRUST:
			motor1.power = command[1];
			motor2.power = command[1];
			motor3.power = command[1];
			motor4.power = command[1];

			receiveMotorCommand(&motor1, 0);
			receiveMotorCommand(&motor2, 0);
			receiveMotorCommand(&motor3, 0);
			receiveMotorCommand(&motor4, 0);
			break;
		}
	}
}

portBASE_TYPE motorSendToQueue(uint8_t *buf, TickType_t n) {
	return xQueueSendToBack(xMotorQueue, buf, n);
}
