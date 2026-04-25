/**
 * @file    uart.h
 * @brief   Minimal UART (USART1) driver for STM32F103 (Blue Pill).
 *
 * Provides blocking transmit functions for printing debug messages over
 * USART1 (PA9 = TX, PA10 = RX) at 115 200 baud, 8N1.
 */

#ifndef DRIVERS_UART_H
#define DRIVERS_UART_H

#include <stdint.h>

/* -------------------------------------------------------------------------
 * Public function prototypes
 * ---------------------------------------------------------------------- */

/**
 * @brief  Initialise USART1 at 115 200 baud (8N1, TX only).
 *
 *         Enables GPIOA and USART1 clocks, configures PA9 as alternate-
 *         function push-pull output, and starts the USART peripheral.
 *
 *         Call this once at the start of main().
 */
void UART_Init(void);

/**
 * @brief  Transmit a single byte over USART1 (blocking).
 *
 * @param  byte  The byte to send.
 */
void UART_SendByte(uint8_t byte);

/**
 * @brief  Transmit a null-terminated string over USART1 (blocking).
 *
 * @param  str  Pointer to the null-terminated string to send.
 */
void UART_SendString(const char *str);

#endif /* DRIVERS_UART_H */
