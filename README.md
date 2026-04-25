# FPT Embedded Bootcamp 2026

Exercises and projects completed during the FPT Embedded Systems Bootcamp for beginners.

---

## Project: STM32 Beginner Starter Project

A minimal bare-metal C project targeting the **STM32F103C8T6** ("Blue Pill") board.
It blinks the on-board LED (PC13) and prints debug messages over USART1 — the
classic "Hello World" for embedded systems.

### Project Structure

```
FPT_EmbeddedBootcamp_2026/
├── main.c              # Application entry point (blink + UART hello)
├── drivers/
│   ├── gpio.h          # GPIO driver – public API
│   ├── gpio.c          # GPIO driver – register-level implementation
│   ├── uart.h          # UART driver – public API
│   └── uart.c          # UART driver – register-level implementation
└── README.md
```

### Hardware Requirements

| Item | Detail |
|------|--------|
| MCU board | STM32F103C8T6 "Blue Pill" |
| On-board LED | PC13 (active LOW) |
| UART TX | PA9 → USB-to-TTL adapter |
| Programmer | ST-Link V2 (SWD) |

### Software Requirements

| Tool | Purpose |
|------|---------|
| [arm-none-eabi-gcc](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain) | Cross-compiler for ARM Cortex-M |
| [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) | All-in-one IDE (optional) |
| [OpenOCD](https://openocd.org/) | On-chip debugger / flash tool |
| Any serial monitor | e.g. PuTTY, Tera Term, `screen` |

### Getting Started

#### 1. Clone the repository

```bash
git clone https://github.com/Tinhuynh3107/FPT_EmbeddedBootcamp_2026.git
cd FPT_EmbeddedBootcamp_2026
```

#### 2. Open in STM32CubeIDE (recommended for beginners)

1. Launch **STM32CubeIDE**.
2. Choose **File → Open Projects from File System…**
3. Select the cloned folder.
4. Press **Build** (hammer icon) to compile.
5. Connect your ST-Link, then press **Run** (play icon) to flash.

#### 3. Build from the command line (advanced)

```bash
arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -g \
    -I. \
    main.c drivers/gpio.c drivers/uart.c \
    -o stm32_blink.elf
```

> **Note:** A full command-line build also needs a linker script and startup
> file for the STM32F103. These are automatically provided by STM32CubeIDE or
> can be taken from the [STM32CubeF1](https://github.com/STMicroelectronics/STM32CubeF1) firmware package.

#### 4. Flash the firmware

```bash
openocd -f interface/stlink.cfg \
        -f target/stm32f1x.cfg \
        -c "program stm32_blink.elf verify reset exit"
```

#### 5. View serial output

Connect a USB-to-TTL adapter to **PA9 (TX)** and open a serial terminal:

| Setting | Value |
|---------|-------|
| Baud rate | 115 200 |
| Data bits | 8 |
| Parity | None |
| Stop bits | 1 |

You should see `STM32 Bootcamp – Hello World!` followed by `Blink!` every second.

---

### What You Will Learn

- How to enable peripheral clocks via the **RCC** registers.
- How to configure **GPIO** pins for output using the CRH/CRL registers.
- How to set up **USART** for basic serial communication.
- The structure of a bare-metal embedded C project (no RTOS, no HAL magic).

---

### Extending the Project

| Task | Hint |
|------|------|
| Add a button | Configure a GPIO pin as input; poll or use EXTI |
| Use HAL instead of bare registers | Replace drivers with `stm32f1xx_hal_gpio.h` calls |
| Add an RTOS | Try [FreeRTOS](https://www.freertos.org/) with STM32CubeMX |
| Send sensor data | Add an I²C or SPI driver in `drivers/` |

---

*Happy hacking! 🚀*
