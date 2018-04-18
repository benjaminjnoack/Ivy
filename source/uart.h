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
#include "fsl_uart.h"
#include "fsl_uart_freertos.h"

#define UART_BUF_SIZE 0x02

void uartInitialize(void);

#endif /* UART_H_ */
