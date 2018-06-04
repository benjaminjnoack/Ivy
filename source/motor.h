/*
 * motor.h
 *
 *  Created on: May 13, 2018
 *      Author: ben
 */

#ifndef MOTOR_H_
#define MOTOR_H_

/**
 * TODO
 * Inputs:
 * 	Orientation Commands
 * 	IMU Readings
 * 	Motor Sensors
 *
 * Outputs:
 *  Motor Control Commands
 */
#include <adafruit_motor.h>
#include "fsl_debug_console.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define LEVEL 0x80
#define MOTOR_COMM_SIZE 0x02

typedef enum {
	AXIS_PITCH = 'P',	//0x50
	AXIS_ROLL = 'R',	//0x52
	AXIS_THRUST = 'T',	//0x54
	AXIS_YAW = 'Y'		//0x59
} axis_cmd_t;

typedef enum {
	MOTOR_ONE,
	MOTOR_TWO,
	MOTOR_THREE,
	MOTOR_FOUR
} motor_t;

typedef struct motor_command {
	motor_t motor;
	uint8_t power;
} motor_command_t;

void motorInitialize(void);

portBASE_TYPE motorSendToQueue(uint8_t *buf, TickType_t n);
portBASE_TYPE receiveMotorCommand(motor_command_t *command, TickType_t n);

#endif /* MOTOR_H_ */
