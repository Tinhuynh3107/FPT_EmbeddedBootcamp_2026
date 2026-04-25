/**
 * @file    main.c
 * @brief   STM32 beginner project – LED blink using GPIO and UART drivers.
 *
 * Hardware target : STM32F103C8T6 ("Blue Pill")
 * PC13 is the on-board LED (active LOW on Blue Pill boards).
 *
 * Build with arm-none-eabi-gcc and the STM32 CMSIS / HAL headers, or
 * open the project in STM32CubeIDE.
 */

#include "drivers/gpio.h"
#include "drivers/uart.h"

/* Simple busy-wait delay (very approximate at 8 MHz HSI) */
static void delay_ms(volatile uint32_t ms)
{
    while (ms--)
    {
        volatile uint32_t i = 8000U; /* ~1 ms at 8 MHz */
        while (i--) { }
    }
}

int main(void)
{
    /* --- Initialise peripherals ---------------------------------------- */
    GPIO_Init();   /* Configure PC13 as push-pull output                    */
    UART_Init();   /* Configure USART1 at 115 200 baud                      */

    UART_SendString("STM32 Bootcamp – Hello World!\r\n");

    /* --- Blink loop ------------------------------------------------------- */
    for (;;)
    {
        GPIO_WritePin(GPIO_PIN_LED, GPIO_PIN_SET);   /* LED off  (active LOW) */
        delay_ms(500U);

        GPIO_WritePin(GPIO_PIN_LED, GPIO_PIN_RESET); /* LED on               */
        delay_ms(500U);

        UART_SendString("Blink!\r\n");
    }

    /* Should never reach here */
    return 0;
}
