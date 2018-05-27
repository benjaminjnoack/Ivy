/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v4.1
processor: MKV31F512xxx12
package_id: MKV31F512VLL12
mcu_data: ksdk2_0
processor_version: 4.0.0
board: FRDM-KV31F
functionalGroups:
- name: BOARD_InitPeripherals
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system_54b53072540eeeb8f8e9343e71f28176'
- global_system_definitions: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * GPIO_1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'GPIO_1'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'GPIOD'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTD_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
    - gpio_config:
      - 0:
        - signal_number: 'GPIO.1'
        - pinDirection: 'kGPIO_DigitalOutput'
        - interrupt_configuration: 'kPORT_InterruptOrDMADisabled'
        - outputLogic: '1U'
      - 1:
        - signal_number: 'GPIO.7'
        - pinDirection: 'kGPIO_DigitalOutput'
        - interrupt_configuration: 'kPORT_InterruptOrDMADisabled'
        - outputLogic: '1U'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
gpio_pin_config_t GPIO_1_config[2] = {
  {
    .pinDirection = kGPIO_DigitalOutput,
    .outputLogic = 1U
  },
  {
    .pinDirection = kGPIO_DigitalOutput,
    .outputLogic = 1U
  }
};

void GPIO_1_init(void) {
  /* Make sure, the clock gate for port D is enabled (e. g. in pin_mux.c) */
  /* Initialize GPIO functionality on pin PTD1 */
  GPIO_PinInit(GPIO_1_GPIO, 1U, &GPIO_1_config[0]);
  /* Initialize GPIO functionality on pin PTD7 */
  GPIO_PinInit(GPIO_1_GPIO, 7U, &GPIO_1_config[1]);
}

/***********************************************************************************************************************
 * GPIO_2 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'GPIO_2'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'GPIOE'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTE_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
    - gpio_config:
      - 0:
        - signal_number: 'GPIO.25'
        - pinDirection: 'kGPIO_DigitalOutput'
        - interrupt_configuration: 'kPORT_InterruptOrDMADisabled'
        - outputLogic: '1U'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
gpio_pin_config_t GPIO_2_config[1] = {
  {
    .pinDirection = kGPIO_DigitalOutput,
    .outputLogic = 1U
  }
};

void GPIO_2_init(void) {
  /* Make sure, the clock gate for port E is enabled (e. g. in pin_mux.c) */
  /* Initialize GPIO functionality on pin PTE25 */
  GPIO_PinInit(GPIO_2_GPIO, 25U, &GPIO_2_config[0]);
}

/***********************************************************************************************************************
 * I2C_1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'I2C_1'
- type: 'i2c'
- mode: 'I2C_Transfer'
- type_id: 'i2c_2566d7363e7e9aaedabb432110e372d7'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'I2C1'
- config_sets:
  - transferCfg:
    - transfer:
      - init_transfer: 'true'
      - master_transfer_cfg:
        - flags: 'kI2C_TransferDefaultFlag'
        - slaveAddress: '64'
        - direction: 'kI2C_Write'
        - subaddress: '0'
        - subaddressSize: '0'
        - dataSize: '5'
      - init_callback: 'true'
      - callback_fcn: 'i2c_master_callback'
      - user_data: ''
  - fsl_i2c:
    - i2c_mode: 'kI2C_Master'
    - clockSource: 'BusInterfaceClock'
    - clockSourceFreq: 'GetFreq'
    - i2c_master_config:
      - enableMaster: 'true'
      - enableStopHold: 'false'
      - baudRate_Bps: '1000000'
      - glitchFilterWidth: '0'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const i2c_master_config_t I2C_1_config = {
  .enableMaster = true,
  .enableStopHold = false,
  .baudRate_Bps = 1000000,
  .glitchFilterWidth = 0
};
i2c_master_handle_t I2C_1_handle;
uint8_t I2C_1_buffer[I2C_1_BUFFER_SIZE];
i2c_master_transfer_t I2C_1_transfer;

void I2C_1_init(void) {
  /* Initialization function */
  I2C_MasterInit(I2C_1_PERIPHERAL, &I2C_1_config, I2C_1_CLK_FREQ);
  I2C_1_transfer.slaveAddress = 64;
  I2C_1_transfer.direction = kI2C_Write;
  I2C_1_transfer.subaddress = (uint32_t)NULL;
  I2C_1_transfer.subaddressSize = 0;
  I2C_1_transfer.data = I2C_1_buffer;
  I2C_1_transfer.dataSize = I2C_1_BUFFER_SIZE;
  I2C_1_transfer.flags = kI2C_TransferDefaultFlag;
  I2C_MasterTransferCreateHandle(I2C_1_PERIPHERAL, &I2C_1_handle, i2c_master_callback, NULL);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Initialize components */
  GPIO_1_init();
  GPIO_2_init();
  I2C_1_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
