/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v4.0
processor: MKV31F512xxx12
package_id: MKV31F512VLL12
mcu_data: ksdk2_0
processor_version: 3.0.1
board: FRDM-KV31F
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '62', peripheral: UART0, signal: RX, pin_signal: PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/EWM_IN}
  - {pin_num: '63', peripheral: UART0, signal: TX, pin_signal: PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/EWM_OUT_b}
  - {pin_num: '73', peripheral: FB, signal: CLKOUT, pin_signal: CMP1_IN1/PTC3/LLWU_P7/SPI0_PCS1/UART1_RX/FTM0_CH2/CLKOUT/LPUART0_RX}
  - {pin_num: '94', peripheral: FTM3, signal: 'CH, 1', pin_signal: ADC0_SE5b/PTD1/SPI0_SCK/UART2_CTS_b/FTM3_CH1/FB_CS0_b/LPUART0_CTS_b, direction: OUTPUT}
  - {pin_num: '32', peripheral: FTM0, signal: 'CH, 1', pin_signal: ADC0_SE18/PTE25/FTM0_CH1/I2C0_SDA/EWM_IN, direction: OUTPUT}
  - {pin_num: '100', peripheral: FTM0, signal: 'CH, 7', pin_signal: PTD7/UART0_TX/FTM0_CH7/FTM0_FLT1/SPI1_SIN, direction: OUTPUT}
  - {pin_num: '1', peripheral: UART1, signal: TX, pin_signal: ADC1_SE4a/PTE0/CLKOUT32K/SPI1_PCS1/UART1_TX/I2C1_SDA}
  - {pin_num: '2', peripheral: UART1, signal: RX, pin_signal: ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/I2C1_SCL/SPI1_SIN}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    /* PORTB16 (pin 62) is configured as UART0_RX */
    PORT_SetPinMux(BOARD_INITPINS_DEBUG_UART_RX_PORT, BOARD_INITPINS_DEBUG_UART_RX_PIN, kPORT_MuxAlt3);

    /* PORTB17 (pin 63) is configured as UART0_TX */
    PORT_SetPinMux(BOARD_INITPINS_DEBUG_UART_TX_PORT, BOARD_INITPINS_DEBUG_UART_TX_PIN, kPORT_MuxAlt3);

    /* PORTC3 (pin 73) is configured as CLKOUT */
    PORT_SetPinMux(BOARD_INITPINS_CMP1_IN1_PORT, BOARD_INITPINS_CMP1_IN1_PIN, kPORT_MuxAlt5);

    /* PORTD1 (pin 94) is configured as FTM3_CH1 */
    PORT_SetPinMux(BOARD_INITPINS_LED_RED_PORT, BOARD_INITPINS_LED_RED_PIN, kPORT_MuxAlt4);

    /* PORTD7 (pin 100) is configured as FTM0_CH7 */
    PORT_SetPinMux(BOARD_INITPINS_LED_GREEN_PORT, BOARD_INITPINS_LED_GREEN_PIN, kPORT_MuxAlt4);

    /* PORTE0 (pin 1) is configured as UART1_TX */
    PORT_SetPinMux(BOARD_INITPINS_UART1_TX_PORT, BOARD_INITPINS_UART1_TX_PIN, kPORT_MuxAlt3);

    /* PORTE1 (pin 2) is configured as UART1_RX */
    PORT_SetPinMux(BOARD_INITPINS_UART1_RX_PORT, BOARD_INITPINS_UART1_RX_PIN, kPORT_MuxAlt3);

    /* PORTE25 (pin 32) is configured as FTM0_CH1 */
    PORT_SetPinMux(BOARD_INITPINS_LED_BLUE_PORT, BOARD_INITPINS_LED_BLUE_PIN, kPORT_MuxAlt3);

    SIM->SOPT2 = ((SIM->SOPT2 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT2_CLKOUTSEL_MASK)))

                  /* CLKOUT select: FlexBus CLKOUT. */
                  | SIM_SOPT2_CLKOUTSEL(SOPT2_CLKOUTSEL_FLEXBUS));

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART0TXSRC_MASK | SIM_SOPT5_UART1TXSRC_MASK)))

                  /* UART 0 transmit data source select: UART0_TX pin. */
                  | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX)

                  /* UART 1 transmit data source select: UART1_TX pin. */
                  | SIM_SOPT5_UART1TXSRC(SOPT5_UART1TXSRC_UART_TX));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
