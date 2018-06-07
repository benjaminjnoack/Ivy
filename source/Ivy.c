/**
 * @file    Ivy.c
 * @brief   Application entry point.
 */
#include <adafruit_motor.h>
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "uart.h"
#include "motor.h"
#include "FreeRTOS.h"
#include "task.h"
#include "fsl_gpio.h"
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
	GPIO_ClearPinsOutput(BOARD_INITPINS_LED_GREEN_GPIO, 1 << BOARD_INITPINS_LED_GREEN_GPIO_PIN);

	vTaskStartScheduler();

	for (;;)
		__asm("NOP");
}
