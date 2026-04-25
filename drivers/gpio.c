/**
 * @file    gpio.c
 * @brief   Minimal GPIO driver implementation for STM32F103 (Blue Pill).
 *
 * Direct register access is used (no HAL dependency) so that beginners can
 * see exactly which bits control the hardware.
 *
 * Reference: STM32F103xx Reference Manual (RM0008), section 9 (GPIO).
 */

#include "gpio.h"

/* -------------------------------------------------------------------------
 * STM32F103 register addresses (from RM0008)
 * ---------------------------------------------------------------------- */

#define RCC_BASE      0x40021000UL
#define RCC_APB2ENR   (*(volatile uint32_t *)(RCC_BASE + 0x18U))

#define GPIOC_BASE    0x40011000UL
#define GPIOC_CRH     (*(volatile uint32_t *)(GPIOC_BASE + 0x04U)) /* CRH: pins 8-15 */
#define GPIOC_ODR     (*(volatile uint32_t *)(GPIOC_BASE + 0x0CU))
#define GPIOC_BSRR    (*(volatile uint32_t *)(GPIOC_BASE + 0x10U))

/* Bit to enable GPIOC clock in RCC_APB2ENR */
#define RCC_APB2ENR_IOPCEN  (1UL << 4U)

/* -------------------------------------------------------------------------
 * Public function implementations
 * ---------------------------------------------------------------------- */

void GPIO_Init(void)
{
    /* 1. Enable GPIOC peripheral clock */
    RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;

    /*
     * 2. Configure PC13 as general-purpose push-pull output at 2 MHz.
     *
     *    CRH controls pins 8-15.  Each pin occupies 4 bits: [CNF1:CNF0:MODE1:MODE0].
     *    Pin 13 occupies bits [23:20] of CRH.
     *
     *    MODE = 10b → output, max speed 2 MHz
     *    CNF  = 00b → general-purpose push-pull output
     */
    GPIOC_CRH &= ~(0xFUL << 20U);   /* Clear bits [23:20] */
    GPIOC_CRH |=  (0x2UL << 20U);   /* Set MODE=10, CNF=00 */

    /* Drive pin HIGH (LED off on Blue Pill, which is active LOW) */
    GPIO_WritePin(GPIO_PIN_LED, GPIO_PIN_SET);
}

void GPIO_WritePin(uint8_t pin, GPIO_PinState state)
{
    if (state == GPIO_PIN_SET)
    {
        /* Set bit: write to BSRR lower half (bits 15:0) */
        GPIOC_BSRR = (1UL << pin);
    }
    else
    {
        /* Reset bit: write to BSRR upper half (bits 31:16) */
        GPIOC_BSRR = (1UL << (pin + 16U));
    }
}

void GPIO_TogglePin(uint8_t pin)
{
    GPIOC_ODR ^= (1UL << pin);
}
