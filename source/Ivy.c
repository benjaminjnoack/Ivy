/**
 * @file    Ivy.c
 * @brief   Application entry point.
 */
#include <adafruit_motor.h>
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKV31F51212.h"
#include "uart.h"
#include "motor.h"
#include "FreeRTOS.h"
#include "task.h"
/*
 * @brief   Application entry point.
 */
int main(void) {
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	BOARD_InitDebugConsole();

	adafruitMotorInitialize();
	motorInitialize();
	uartInitialize();
	printf("Initialization Complete\r\n");

	vTaskStartScheduler();

	for (;;)
		__asm("NOP");
}
