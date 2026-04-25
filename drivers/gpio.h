/**
 * @file    gpio.h
 * @brief   Minimal GPIO driver for STM32F103 (Blue Pill).
 *
 * This driver wraps the CMSIS register-level access for the on-board LED
 * (PC13) so that beginners can call simple functions without worrying about
 * bit manipulation.
 */

#ifndef DRIVERS_GPIO_H
#define DRIVERS_GPIO_H

#include <stdint.h>

/* -------------------------------------------------------------------------
 * Public constants
 * ---------------------------------------------------------------------- */

/** On-board LED pin (PC13 on Blue Pill, active LOW). */
#define GPIO_PIN_LED   13U

/** Pin state values passed to GPIO_WritePin(). */
typedef enum
{
    GPIO_PIN_RESET = 0U, /**< Drive pin LOW  */
    GPIO_PIN_SET   = 1U  /**< Drive pin HIGH */
} GPIO_PinState;

/* -------------------------------------------------------------------------
 * Public function prototypes
 * ---------------------------------------------------------------------- */

/**
 * @brief  Initialise GPIOC and configure PC13 as a push-pull output.
 *
 *         Call this once at the start of main() before using any other
 *         GPIO functions.
 */
void GPIO_Init(void);

/**
 * @brief  Write a state to an output pin on GPIOC.
 *
 * @param  pin    Pin number (0-15).
 * @param  state  GPIO_PIN_SET to drive HIGH, GPIO_PIN_RESET to drive LOW.
 */
void GPIO_WritePin(uint8_t pin, GPIO_PinState state);

/**
 * @brief  Toggle the state of an output pin on GPIOC.
 *
 * @param  pin  Pin number (0-15).
 */
void GPIO_TogglePin(uint8_t pin);

#endif /* DRIVERS_GPIO_H */
