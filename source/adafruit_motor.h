/*
 * pca9685.h
 *
 *  Created on: May 7, 2018
 *      Author: ben
 */

#ifndef ADAFRUIT_MOTOR_H_
#define ADAFRUIT_MOTOR_H_

#include "string.h"
#include "fsl_debug_console.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "fsl_i2c.h"
#include "peripherals.h"
#include "motor.h"

#define ALL_CALL_ADDRESS 0x00
#define PCA9685_ADDRESS 0x60
#define SWRST_ADDRESS 0x06

#define MODE1_ADDRESS 0x00
#define MODE1_ALLCALL 1 << 0
#define MODE1_AI 1 << 5

#define MODE2_OUTDRV 1 << 2
#define MODE2_OCH 1 << 3

/**
 * The same bit written to different registers means either full on or full off
 */
#define FULL_OFF 1 << 4
#define FULL_ON 1 << 4

void adafruitMotorInitialize(void);

#endif /* ADAFRUIT_MOTOR_H_ */
