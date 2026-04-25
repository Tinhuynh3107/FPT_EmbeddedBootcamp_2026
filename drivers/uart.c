/**
 * @file    uart.c
 * @brief   Minimal UART (USART1) driver implementation for STM32F103 (Blue Pill).
 *
 * Direct register access is used so that beginners can see exactly which
 * bits control the peripheral.
 *
 * Reference: STM32F103xx Reference Manual (RM0008), section 27 (USART).
 */

#include "uart.h"

/* -------------------------------------------------------------------------
 * STM32F103 register addresses (from RM0008)
 * ---------------------------------------------------------------------- */

#define RCC_BASE        0x40021000UL
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18U))

/* GPIOA – PA9 is USART1_TX */
#define GPIOA_BASE      0x40010800UL
#define GPIOA_CRH       (*(volatile uint32_t *)(GPIOA_BASE + 0x04U))

/* USART1 */
#define USART1_BASE     0x40013800UL
#define USART1_SR       (*(volatile uint32_t *)(USART1_BASE + 0x00U))
#define USART1_DR       (*(volatile uint32_t *)(USART1_BASE + 0x04U))
#define USART1_BRR      (*(volatile uint32_t *)(USART1_BASE + 0x08U))
#define USART1_CR1      (*(volatile uint32_t *)(USART1_BASE + 0x0CU))

/* RCC_APB2ENR bits */
#define RCC_APB2ENR_IOPAEN   (1UL << 2U)  /* GPIOA clock enable  */
#define RCC_APB2ENR_USART1EN (1UL << 14U) /* USART1 clock enable */

/* USART_SR bits */
#define USART_SR_TXE   (1UL << 7U) /* Transmit data register empty */
#define USART_SR_TC    (1UL << 6U) /* Transmission complete        */

/* USART_CR1 bits */
#define USART_CR1_UE   (1UL << 13U) /* USART enable */
#define USART_CR1_TE   (1UL << 3U)  /* Transmitter enable */

/*
 * BRR value for 115 200 baud at 8 MHz (HSI, no PLL):
 *   USARTDIV = 8 000 000 / (16 * 115 200) = 4.340...
 *   Mantissa = 4  → bits [15:4] = 0x004
 *   Fraction = 0.340 * 16 ≈ 5 → bits [3:0] = 0x5
 *   BRR = 0x0045
 */
#define USART1_BRR_115200_8MHZ  0x0045UL

/* -------------------------------------------------------------------------
 * Public function implementations
 * ---------------------------------------------------------------------- */

void UART_Init(void)
{
    /* 1. Enable clocks for GPIOA and USART1 */
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;

    /*
     * 2. Configure PA9 (USART1_TX) as alternate-function push-pull, 2 MHz.
     *    PA9 is in CRH, bits [7:4].
     *    MODE = 10b (output 2 MHz), CNF = 10b (AF push-pull) → 0xA
     */
    GPIOA_CRH &= ~(0xFUL << 4U);  /* Clear PA9 config bits */
    GPIOA_CRH |=  (0xAUL << 4U);  /* AF push-pull, 2 MHz   */

    /* 3. Set baud rate */
    USART1_BRR = USART1_BRR_115200_8MHZ;

    /* 4. Enable USART1 transmitter and the USART itself */
    USART1_CR1 = USART_CR1_TE | USART_CR1_UE;
}

void UART_SendByte(uint8_t byte)
{
    /* Wait until the transmit data register is empty */
    while (!(USART1_SR & USART_SR_TXE)) { }
    USART1_DR = byte;
}

void UART_SendString(const char *str)
{
    while (*str)
    {
        UART_SendByte((uint8_t)*str);
        str++;
    }
    /* Wait for the last byte to finish transmitting */
    while (!(USART1_SR & USART_SR_TC)) { }
}
