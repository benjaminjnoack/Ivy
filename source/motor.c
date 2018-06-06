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

int pitch, roll, thrust, yaw;

void motorCalculatePower();
void motorTask(void *pvParameters);

void motorInitialize(void) {
	BaseType_t xReturn;
	uint16_t xTaskDepth;

	pitch = (MIN_POWER | HALF_DYNAMIC_RANGE);
	roll = (MIN_POWER | HALF_DYNAMIC_RANGE);
	thrust = (MIN_POWER | HALF_DYNAMIC_RANGE);
	yaw = (MIN_POWER | HALF_DYNAMIC_RANGE);

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
			break;
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

	if (pitch > HALF_DYNAMIC_RANGE) {
		m1 += (pitch - HALF_DYNAMIC_RANGE);
		m4 += (pitch - HALF_DYNAMIC_RANGE);
		m2 -= (pitch - HALF_DYNAMIC_RANGE);
		m3 -= (pitch - HALF_DYNAMIC_RANGE);
	} else {
		m1 -= pitch;
		m4 -= pitch;
		m2 += pitch;
		m3 += pitch;
	}

	if (roll > HALF_DYNAMIC_RANGE) {
		m1 += (roll - HALF_DYNAMIC_RANGE);
		m2 += (roll - HALF_DYNAMIC_RANGE);
		m3 -= (roll - HALF_DYNAMIC_RANGE);
		m4 -= (roll - HALF_DYNAMIC_RANGE);
	} else {
		m1 -= roll;
		m2 -= roll;
		m3 += roll;
		m4 += roll;
	}

	if (yaw > HALF_DYNAMIC_RANGE) {//CW
		m1 -= (yaw - HALF_DYNAMIC_RANGE);
		m2 += (yaw - HALF_DYNAMIC_RANGE);
		m3 -= (yaw - HALF_DYNAMIC_RANGE);
		m4 += (yaw - HALF_DYNAMIC_RANGE);
	} else {//CCW
		m1 += yaw;
		m2 -= yaw;
		m3 += yaw;
		m4 -= yaw;
	}
	//TODO use saturation math to prevent this check
	if (m1 > 0xFF) {
		m1 = 0xFF;
	}

	if (m2 > 0xFF) {
		m2 = 0xFF;
	}

	if (m3 > 0xFF) {
		m3 = 0xFF;
	}

	if (m4 > 0xFF) {
		m4 = 0xFF;
	}

	/**
	 * Shift over one to axe the LSB
	 * then ensure the MSB is set
	 * Makes the dynamic range 0x80 to 0xFF
	 */
	m1 = (m1 >> 1) | MIN_POWER;
	m2 = (m2 >> 1) | MIN_POWER;
	m3 = (m3 >> 1) | MIN_POWER;
	m4 = (m4 >> 1) | MIN_POWER;

	motor1.power = (uint8_t) m1;
	motor2.power = (uint8_t) m2;
	motor3.power = (uint8_t) m3;
	motor4.power = (uint8_t) m4;
}

portBASE_TYPE motorSendToQueue(uint8_t *buf, TickType_t n) {
	return xQueueSendToBack(xMotorQueue, buf, n);
}
