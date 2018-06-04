/*
 * motor.c
 *
 *  Created on: May 13, 2018
 *      Author: ben
 */

#include "motor.h"

QueueHandle_t xMotorQueue;
TaskHandle_t xMotorTask;

static motor_command_t motor1 = {.motor = MOTOR_ONE, .power = 0x00};
static motor_command_t motor2 = {.motor = MOTOR_TWO, .power = 0x00};
static motor_command_t motor3 = {.motor = MOTOR_THREE, .power = 0x00};
static motor_command_t motor4 = {.motor = MOTOR_FOUR, .power = 0x00};

int pitch, roll, thrust, yaw = LEVEL;

void motorCalculatePower();
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
			pitch = command[1];
			break;
		case AXIS_ROLL:
			roll = command[1];
		case AXIS_THRUST:
			thrust = command[1];
			break;
		case AXIS_YAW:
			yaw = command[1];
			break;
		}

		motorCalculatePower();
		//TODO turn this into a single command - or figure out which motors changed
		receiveMotorCommand(&motor1, 0);
		receiveMotorCommand(&motor2, 0);
		receiveMotorCommand(&motor3, 0);
		receiveMotorCommand(&motor4, 0);
	}
}

void motorCalculatePower() {
	int m1, m2, m3, m4;

	m1 = thrust;
	m2 = thrust;
	m3 = thrust;
	m4 = thrust;

	if (pitch > LEVEL) {
		m1 += (pitch - LEVEL);
		m4 += (pitch - LEVEL);
		m2 -= (pitch - LEVEL);
		m3 -= (pitch - LEVEL);
	} else if (pitch < LEVEL) {
		m1 -= pitch;
		m4 -= pitch;
		m2 += pitch;
		m3 += pitch;
	}

	if (roll > LEVEL) {
		m1 += (roll - LEVEL);
		m2 += (roll - LEVEL);
		m3 -= (roll - LEVEL);
		m4 -= (roll - LEVEL);
	} else if (roll < LEVEL) {
		m1 -= roll;
		m2 -= roll;
		m3 += roll;
		m4 += roll;
	}

	if (yaw > LEVEL) {//CW
		m1 += (yaw - LEVEL);
		m2 -= (yaw - LEVEL);
		m3 -= (yaw - LEVEL);
		m4 += (yaw - LEVEL);
	} else if (yaw < LEVEL) {//CCW
		m1 -= yaw;
		m2 += yaw;
		m3 += yaw;
		m4 -= yaw;
	}
	//TODO use saturation math to prevent this check
	if (m1 > 0xFF) {
		m1 = 0xFF;
	} else if (m1 < 0) {
		m1 = 0x00;
	}

	if (m2 > 0xFF) {
		m2 = 0xFF;
	} else if (m2 < 0) {
		m2 = 0x00;
	}

	if (m3 > 0xFF) {
		m3 = 0xFF;
	} else if (m3 < 0) {
		m3 = 0x00;
	}

	if (m4 > 0xFF) {
		m4 = 0xFF;
	} else if (m4 < 0) {
		m4 = 0x00;
	}

	motor1.power = m1;
	motor2.power = m2;
	motor3.power = m3;
	motor4.power = m4;
}

portBASE_TYPE motorSendToQueue(uint8_t *buf, TickType_t n) {
	return xQueueSendToBack(xMotorQueue, buf, n);
}
