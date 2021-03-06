/*
    RExOS - embedded RTOS
    Copyright (c) 2011-2016, Alexey Kramarenko
    All rights reserved.
*/

#ifndef CONFIG_H
#define CONFIG_H

// =============================== LEDS ========================================
#define LED_COUNT                                   4
#define LED_RED_PIN                                 A1
#define LED_BLUE_PIN                                A2
#define LED_ORANGE_PIN                              A3

#define LED_MAX_BRIGHT                              0xFF
#define LED_BLINK_FREQ_HZ                           25
#define LED_BLINK_TIMES                             3

#define LED_TIM_REG                                 TIM2
#define LED_TIM                                     TIM_2
#define LED_RED_CHANNEL                             TIM_CHANNEL2
#define LED_BLUE_CHANNEL                            TIM_CHANNEL3
#define LED_ORANGE_CHANNEL                          TIM_CHANNEL4

#define LED_BLINK_TIM_REG                           TIM3
#define LED_BLINK_TIM                               TIM_3
#define LED_BLINK_TIM_CHANNEL                       TIM_CHANNEL1
#define LED_BLINK_IRQ_VECTOR                        TIM3_IRQn

// =============================== USB =========================================
#define USB_PORT_NUM                                USB_0
#define USBD_PROCESS_SIZE                           1200
#define USBD_PROCESS_PRIORITY                       150

// ============================== CCID  ========================================
#define USB_CCID_INTERFACE                          0

// =============================== COMM ========================================
#define COMM_COMMAND_END                            0x0D

// ================================= DEBUG =====================================

#define DBG_CONSOLE                                 UART_1
#define DBG_CONSOLE_TX_PIN                          A9
#define DBG_CONSOLE_BAUD                            115200

#define TEST_ROUNDS                                 10000

#define APP_DEBUG                                   1
#define APP_DEBUG_ERRORS                            1

#define APP_DEBUG_USB                               1
#define APP_DEBUG_CCID                              1
#define APP_DEBUG_NFC                               1

#endif // CONFIG_H
