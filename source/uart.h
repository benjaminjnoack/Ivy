/*
 * uart.h
 *
 *  Created on: Apr 16, 2018
 *      Author: ben
 */

#ifndef UART_H_
#define UART_H_

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "fsl_clock.h"
#include "fsl_uart.h"
#include "fsl_debug_console.h"

#define UART_RX_BUFFER_LENGTH 100

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void uartInitialize(void);

#endif /* UART_H_ */
