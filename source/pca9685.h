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
 * responds to all call and reset
 * 1MHz FM+ I2C
 * Motors can be updated one by one, or on the STOP command
 * External clock (useful?) currently grounded, needs software and hardware
 * Defaults to change on stop and no sequential increment
 */
#include "string.h"
#include "fsl_debug_console.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "fsl_i2c.h"
#include "peripherals.h"
#include "motor.h"

#define PCA9685_ADDRESS 0x60
#define SWRST_ADDRESS 0x00
#define RX_BUFFER_SIZE 0x04


void pca9685Initialize(void);

#endif /* PCA9685_H_ */
