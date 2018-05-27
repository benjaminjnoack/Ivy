/*
 * pca9685.h
 *
 *  Created on: May 7, 2018
 *      Author: ben
 */

#ifndef PCA9685_H_
#define PCA9685_H_

/**
 * TODO
 * Motors can be updated one by one, or on the STOP command
 * External clock (useful?) currently grounded, needs software and hardware
 * Defaults to change on stop and no sequential increment
 *
 * Mapping of TB6612 to PCA9685 signals
 * Motor 3 CCW: A02
 * 	PWMA - PWM2 0
 * 	AIN2 - PWM3 high
 * 	AIN1 - PWM4 low
 *
 * Motor 4 CW: A01
 * 	BIN1 - PWM5 high
 * 	BIN2 - PWM6 low
 * 	PWMB - PWM7 0
 *
 * Motor 1 CCW: A02
 * 	PWMA - PWM8 0
 * 	AIN2 - PWM9 high
 * 	AIN1 - PWM10 low
 *
 * Motor 2 CW: A01
 * 	BIN1 - PWM11 high
 * 	BIN2 - PWM12 low
 * 	PWMB - PWM13 0
 */
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

void pca9685Initialize(void);

#endif /* PCA9685_H_ */
