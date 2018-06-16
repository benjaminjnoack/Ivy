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

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "event_groups.h"

// KSDK & ISSDK Headers
#include "fsl_debug_console.h"  // KSDK header file for the debug interface
#include "board.h"              // KSDK header file to define board configuration
#include "pin_mux.h"            // KSDK header file for pin mux initialization functions
#include "clock_config.h"       // KSDK header file for clock configuration
#ifndef CPU_LPC54114J256BD64_cm4
#include "fsl_port.h"           // KSDK header file for Port I/O control
#endif
#include "fsl_i2c.h"            // KSDK header file for I2C interfaces
#include "fxas21002.h"          // register address and bit field definitions
#include "fxos8700.h"           // register address and bit field definitions
#include "register_io_i2c.h"
#include "fsl_i2c_cmsis.h"

// Sensor Fusion Headers
#include "sensor_fusion.h"      // top level magCal and sensor fusion interfaces
#include "control.h"  	        // Command/Streaming interface - application specific
#include "status.h"   	        // Sta:tus indicator interface - application specific
#include "drivers.h"  	        // NXP sensor drivers OR customer-supplied drivers

// Global data structures
SensorFusionGlobals sfg;                ///< This is the primary sensor fusion data structure
ControlSubsystem controlSubsystem;      ///< used for serial communications
StatusSubsystem statusSubsystem;        ///< provides visual (usually LED) status indicator
struct PhysicalSensor sensors[2];              ///< This implementation uses two physical sensors
EventGroupHandle_t event_group = NULL;
registerDeviceInfo_t i2cBusInfo = {
    .deviceInstance     = I2C_S_DEVICE_INDEX,
    .functionParam      = NULL,
    .idleFunction       = NULL
};

static void read_task(void *pvParameters);              // FreeRTOS Task definition
static void fusion_task(void *pvParameters);            // FreeRTOS Task definition


/*
 * @brief   Application entry point.
 */
int main(void) {
	BOARD_InitBootClocks();
	BOARD_InitPins();                   // defined in pin_mux.c, initializes pkg pins
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();           // defined in board.c, initializes the OpenSDA port

//	adafruitMotorInitialize();
//	motorInitialize();
//	uartInitialize()

    ARM_DRIVER_I2C* I2Cdrv = &I2C_S_DRIVER;       // defined in the <shield>.h file
    I2Cdrv->Initialize(I2C_S_SIGNAL_EVENT);  // Initialize the KSDK driver for the I2C port
    I2Cdrv->PowerControl(ARM_POWER_FULL);      // Set the I2C Power mode.
    I2Cdrv->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST); // Set the I2C bus speed.

    initializeControlPort(&controlSubsystem);                           // configure pins and ports for the control sub-system
    initializeStatusSubsystem(&statusSubsystem);                        // configure pins and ports for the status sub-system
    initSensorFusionGlobals(&sfg, &statusSubsystem, &controlSubsystem); // Initialize sensor fusion structures
    // "install" the sensors we will be using
    sfg.installSensor(&sfg, &sensors[0], FXOS8700_I2C_ADDR, 1, (void*) I2Cdrv, &i2cBusInfo, FXOS8700_Init,  FXOS8700_Read);
    sfg.installSensor(&sfg, &sensors[1], FXAS21002_I2C_ADDR, 1, (void*) I2Cdrv, &i2cBusInfo, FXAS21002_Init, FXAS21002_Read);
    sfg.initializeFusionEngine(&sfg);	        // This will initialize sensors and magnetic calibration

    event_group = xEventGroupCreate();
    xTaskCreate(read_task, "READ", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(fusion_task, "FUSION", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    sfg.setStatus(&sfg, NORMAL);                // If we got this far, let's set status state to NORMAL
    vTaskStartScheduler();                      // Start the RTOS scheduler
    sfg.setStatus(&sfg, HARD_FAULT);            // If we got this far, FreeRTOS does not have enough memory allocated
    for (;;) ;

}

static void read_task(void *pvParameters)
{
    uint16_t i=0;                       // general counter variable
    portTickType lastWakeTime;
    const portTickType frequency = 1;   // tick counter runs at the read rate
    lastWakeTime = xTaskGetTickCount();
    while (1)
    {
        for (i=1; i<=OVERSAMPLE_RATE; i++) {
            vTaskDelayUntil(&lastWakeTime, frequency);
            sfg.readSensors(&sfg, i);              // Reads sensors, applies HAL and does averaging (if applicable)
        }
        xEventGroupSetBits(event_group, B0);
    }
}

static void fusion_task(void *pvParameters)
{
    uint16_t i=0;  // general counter variable
    while (1)
    {
        xEventGroupWaitBits(event_group,    /* The event group handle. */
                            B0,             /* The bit pattern the event group is waiting for. */
                            pdTRUE,         /* BIT_0 and BIT_4 will be cleared automatically. */
                            pdFALSE,        /* Don't wait for both bits, either bit unblock task. */
                            portMAX_DELAY); /* Block indefinitely to wait for the condition to be met. */

        sfg.conditionSensorReadings(&sfg);  // magCal is run as part of this
        sfg.runFusion(&sfg);                // Run the actual fusion algorithms
        sfg.applyPerturbation(&sfg);        // apply debug perturbation (testing only)

        sfg.loopcounter++;                  // The loop counter is used to "serialize" mag cal operations
        i=i+1;
        if (i>=4) {                         // Some status codes include a "blink" feature.  This loop
                i=0;                        // should cycle at least four times for that to operate correctly.
                sfg.updateStatus(&sfg);     // This is where pending status updates are made visible
        }
        sfg.queueStatus(&sfg, NORMAL);      // assume NORMAL status for next pass through the loop
        sfg.pControlSubsystem->stream(&sfg, sUARTOutputBuffer);      // Send stream data to the Sensor Fusion Toolbox
    }
}

/// \endcode

