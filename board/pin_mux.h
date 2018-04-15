/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
    kPIN_MUX_DirectionInput = 0U,        /* Input direction */
    kPIN_MUX_DirectionOutput = 1U,       /* Output direction */
    kPIN_MUX_DirectionInputOrOutput = 2U /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define SOPT2_CLKOUTSEL_FLEXBUS 0x00u  /*!<@brief CLKOUT select: FlexBus CLKOUT */
#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */

/*! @name PORTB16 (number 62), U7[4]/UART0_RX_TGTMCU
  @{ */
#define BOARD_INITPINS_DEBUG_UART_RX_PERIPHERAL UART0              /*!<@brief Device name: UART0 */
#define BOARD_INITPINS_DEBUG_UART_RX_SIGNAL RX                     /*!<@brief UART0 signal: RX */
#define BOARD_INITPINS_DEBUG_UART_RX_PORT PORTB                    /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_DEBUG_UART_RX_PIN 16U                       /*!<@brief PORTB pin index: 16 */
#define BOARD_INITPINS_DEBUG_UART_RX_PIN_NAME UART0_RX             /*!<@brief Pin name */
#define BOARD_INITPINS_DEBUG_UART_RX_LABEL "U7[4]/UART0_RX_TGTMCU" /*!<@brief Label */
#define BOARD_INITPINS_DEBUG_UART_RX_NAME "DEBUG_UART_RX"          /*!<@brief Identifier name */
                                                                   /* @} */

/*! @name PORTB17 (number 63), U10[1]/UART0_TX_TGTMCU
  @{ */
#define BOARD_INITPINS_DEBUG_UART_TX_PERIPHERAL UART0               /*!<@brief Device name: UART0 */
#define BOARD_INITPINS_DEBUG_UART_TX_SIGNAL TX                      /*!<@brief UART0 signal: TX */
#define BOARD_INITPINS_DEBUG_UART_TX_PORT PORTB                     /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_DEBUG_UART_TX_PIN 17U                        /*!<@brief PORTB pin index: 17 */
#define BOARD_INITPINS_DEBUG_UART_TX_PIN_NAME UART0_TX              /*!<@brief Pin name */
#define BOARD_INITPINS_DEBUG_UART_TX_LABEL "U10[1]/UART0_TX_TGTMCU" /*!<@brief Label */
#define BOARD_INITPINS_DEBUG_UART_TX_NAME "DEBUG_UART_TX"           /*!<@brief Identifier name */
                                                                    /* @} */

/*! @name PORTD1 (number 94), D4[1]/LEDRGB_RED
  @{ */
#define BOARD_INITPINS_LED_RED_PERIPHERAL GPIOD                   /*!<@brief Device name: GPIOD */
#define BOARD_INITPINS_LED_RED_SIGNAL GPIO                        /*!<@brief GPIOD signal: GPIO */
#define BOARD_INITPINS_LED_RED_GPIO GPIOD                         /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_LED_RED_GPIO_PIN 1U                        /*!<@brief PORTD pin index: 1 */
#define BOARD_INITPINS_LED_RED_PORT PORTD                         /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_LED_RED_PIN 1U                             /*!<@brief PORTD pin index: 1 */
#define BOARD_INITPINS_LED_RED_CHANNEL 1                          /*!<@brief GPIOD GPIO channel: 1 */
#define BOARD_INITPINS_LED_RED_PIN_NAME PTD1                      /*!<@brief Pin name */
#define BOARD_INITPINS_LED_RED_LABEL "D4[1]/LEDRGB_RED"           /*!<@brief Label */
#define BOARD_INITPINS_LED_RED_NAME "LED_RED"                     /*!<@brief Identifier name */
#define BOARD_INITPINS_LED_RED_DIRECTION kPIN_MUX_DirectionOutput /*!<@brief Direction */
                                                                  /* @} */

/*! @name PORTD7 (number 100), D4[4]/LEDRGB_GREEN
  @{ */
#define BOARD_INITPINS_LED_GREEN_PERIPHERAL GPIOD                   /*!<@brief Device name: GPIOD */
#define BOARD_INITPINS_LED_GREEN_SIGNAL GPIO                        /*!<@brief GPIOD signal: GPIO */
#define BOARD_INITPINS_LED_GREEN_GPIO GPIOD                         /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_LED_GREEN_GPIO_PIN 7U                        /*!<@brief PORTD pin index: 7 */
#define BOARD_INITPINS_LED_GREEN_PORT PORTD                         /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_LED_GREEN_PIN 7U                             /*!<@brief PORTD pin index: 7 */
#define BOARD_INITPINS_LED_GREEN_CHANNEL 7                          /*!<@brief GPIOD GPIO channel: 7 */
#define BOARD_INITPINS_LED_GREEN_PIN_NAME PTD7                      /*!<@brief Pin name */
#define BOARD_INITPINS_LED_GREEN_LABEL "D4[4]/LEDRGB_GREEN"         /*!<@brief Label */
#define BOARD_INITPINS_LED_GREEN_NAME "LED_GREEN"                   /*!<@brief Identifier name */
#define BOARD_INITPINS_LED_GREEN_DIRECTION kPIN_MUX_DirectionOutput /*!<@brief Direction */
                                                                    /* @} */

/*! @name PORTE25 (number 32), D4[3]/LEDRGB_BLUE
  @{ */
#define BOARD_INITPINS_LED_BLUE_PERIPHERAL GPIOE                   /*!<@brief Device name: GPIOE */
#define BOARD_INITPINS_LED_BLUE_SIGNAL GPIO                        /*!<@brief GPIOE signal: GPIO */
#define BOARD_INITPINS_LED_BLUE_GPIO GPIOE                         /*!<@brief GPIO device name: GPIOE */
#define BOARD_INITPINS_LED_BLUE_GPIO_PIN 25U                       /*!<@brief PORTE pin index: 25 */
#define BOARD_INITPINS_LED_BLUE_PORT PORTE                         /*!<@brief PORT device name: PORTE */
#define BOARD_INITPINS_LED_BLUE_PIN 25U                            /*!<@brief PORTE pin index: 25 */
#define BOARD_INITPINS_LED_BLUE_CHANNEL 25                         /*!<@brief GPIOE GPIO channel: 25 */
#define BOARD_INITPINS_LED_BLUE_PIN_NAME PTE25                     /*!<@brief Pin name */
#define BOARD_INITPINS_LED_BLUE_LABEL "D4[3]/LEDRGB_BLUE"          /*!<@brief Label */
#define BOARD_INITPINS_LED_BLUE_NAME "LED_BLUE"                    /*!<@brief Identifier name */
#define BOARD_INITPINS_LED_BLUE_DIRECTION kPIN_MUX_DirectionOutput /*!<@brief Direction */
                                                                   /* @} */

/*! @name PORTC3 (number 73), J1[14]/LLWU_P7/CMP1_IN1
  @{ */
#define BOARD_INITPINS_CMP1_IN1_PERIPHERAL FB                   /*!<@brief Device name: FB */
#define BOARD_INITPINS_CMP1_IN1_SIGNAL CLKOUT                   /*!<@brief FB signal: CLKOUT */
#define BOARD_INITPINS_CMP1_IN1_PORT PORTC                      /*!<@brief PORT device name: PORTC */
#define BOARD_INITPINS_CMP1_IN1_PIN 3U                          /*!<@brief PORTC pin index: 3 */
#define BOARD_INITPINS_CMP1_IN1_PIN_NAME CLKOUT                 /*!<@brief Pin name */
#define BOARD_INITPINS_CMP1_IN1_LABEL "J1[14]/LLWU_P7/CMP1_IN1" /*!<@brief Label */
#define BOARD_INITPINS_CMP1_IN1_NAME "CMP1_IN1"                 /*!<@brief Identifier name */
                                                                /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
