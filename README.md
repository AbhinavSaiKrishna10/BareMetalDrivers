
# BareMetalDrivers

A modular bare-metal firmware project for ARM Cortex-M4 written in Embedded C without vendor HAL libraries.

The project implements low-level peripheral drivers by directly accessing STM32F411 hardware registers through memory-mapped I/O.

## Goals

- Learn ARM Cortex-M architecture
- Understand memory-mapped I/O
- Implement reusable peripheral drivers
- Understand startup code and vector tables
- Write a custom linker script
- Build firmware using the ARM GNU Toolchain
- Debug and inspect ELF firmware using GDB
- Develop firmware suitable for deployment on STM32 hardware

## Target Platform

- MCU: STM32F411xE
- Core: ARM Cortex-M4
- Architecture: ARMv7E-M
- Flash: 512 KB
- SRAM: 128 KB
- Default system clock: 16 MHz HSI

## Project Architecture

```text
                         Bare-Metal Firmware
                                  |
                                  v
                             main.c
                                  |
                +-----------------+-----------------+
                |                 |                 |
                v                 v                 v
              GPIO              UART              Timer
                |                 |                 |
                +-----------------+-----------------+
                                  |
                                  v
                         Peripheral Drivers
                                  |
                +-----------------+-----------------+
                |                 |                 |
                v                 v                 v
               RCC              EXTI              NVIC
                |                 |                 |
                +-----------------+-----------------+
                                  |
                                  v
                     STM32F411 Memory-Mapped
                           Registers
                                  |
                                  v
                            Hardware
````

### Firmware Layers

```text
Application Layer
        |
        v
     main.c
        |
        v
Driver Layer
        |
        +-- RCC
        +-- GPIO
        +-- UART
        +-- SysTick
        +-- Timer
        +-- NVIC
        +-- EXTI
        |
        v
Register Layer
        |
        +-- STM32 peripheral registers
        +-- Cortex-M4 core registers
        |
        v
Hardware
```

## Implemented Drivers

### RCC

Responsible for enabling peripheral clocks through the STM32F411 RCC registers.

Implemented functionality:

- GPIO peripheral clock enable
- USART peripheral clock enable
- Timer peripheral clock enable
- SYSCFG clock enable

### GPIO

Provides register-level GPIO configuration and control.

Implemented functionality:

- Input/output/alternate-function/analog modes
- Digital pin read
- Digital pin write
- Pin toggle
- Pull-up/pull-down configuration
- Push-pull/open-drain configuration
- GPIO speed configuration
- Alternate-function selection

### UART

Provides basic USART1 communication.

Configuration:

- USART1
- PA9 → TX
- PA10 → RX
- Alternate Function 7
- 115200 baud
- 16 MHz system clock

Implemented functionality:

- UART initialization
- Byte transmission
- Byte reception
- String transmission

### SysTick

Provides a basic millisecond delay using the Cortex-M4 SysTick peripheral.

Implemented functionality:

- SysTick initialization
- Millisecond delay

### Timer

Provides basic TIM2 timer control.

Implemented functionality:

- Timer initialization
- Prescaler configuration
- Auto-reload configuration
- Timer start/stop
- Counter reset
- Update-event detection
- Update interrupt enable

### NVIC

Provides basic Cortex-M4 interrupt-controller operations.

Implemented functionality:

- IRQ enable
- IRQ disable
- IRQ pending
- Pending clear
- IRQ priority configuration

### EXTI

Provides external interrupt configuration using EXTI and SYSCFG.

Implemented functionality:

- GPIO-to-EXTI line mapping
- Rising-edge trigger
- Falling-edge trigger
- Both-edge trigger
- Interrupt enable/disable
- Pending flag handling
- Software interrupt triggering

## Memory Map

The firmware uses the STM32F411 memory regions defined by the linker script.

| RegionAddressSize          |              |                        |
| -------------------------- | ------------ | ---------------------- |
| Flash                      | `0x08000000` | 512 KB                 |
| SRAM                       | `0x20000000` | 128 KB                 |
| Peripheral space           | `0x40000000` | Peripheral region      |
| Cortex-M4 core peripherals | `0xE000E000` | Core peripheral region |

### Firmware Memory Layout

```text
Flash
0x08000000
    |
    +-----------------------+
    | Vector Table          |
    | .isr_vector           |
    +-----------------------+
    | Program Code          |
    | .text                 |
    +-----------------------+
    | Read-only Data        |
    | .rodata               |
    +-----------------------+
    |                       |
    | Remaining Flash       |
    |                       |
0x08080000
```

```text
SRAM
0x20000000
    |
    +-----------------------+
    | Initialized Data      |
    | .data                 |
    +-----------------------+
    | Zero Initialized Data |
    | .bss                  |
    +-----------------------+
    |                       |
    | Stack                 |
    |                       |
0x20020000
```

### Cortex-M4 Core Peripheral Region

```text
0xE000E000
    |
    +-- SysTick
    |   0xE000E010
    |
    +-- NVIC
    |   0xE000E100
    |
    +-- SCB
        0xE000ED00
```

## Peripheral Register Map

Important STM32F411 peripheral base addresses used by the drivers:

| PeripheralBase Address |              |
| ---------------------- | ------------ |
| TIM2                   | `0x40000000` |
| GPIOA                  | `0x40020000` |
| GPIOB                  | `0x40020400` |
| GPIOC                  | `0x40020800` |
| GPIOD                  | `0x40020C00` |
| GPIOE                  | `0x40021000` |
| GPIOH                  | `0x40021C00` |
| RCC                    | `0x40023800` |
| USART1                 | `0x40011000` |
| USART2                 | `0x40004400` |
| USART6                 | `0x40011400` |
| SYSCFG                 | `0x40013800` |
| EXTI                   | `0x40013C00` |

## Startup and Linker

### Startup Code

`startup/startup.s` provides:

- Cortex-M4 vector table
- Initial stack pointer
- Reset handler
- Default interrupt handler
- NMI handler
- HardFault handler
- External interrupt vector entries

The reset vector points to `Reset_Handler`.

### Linker Script

`linker/linker.ld` defines:

- Flash memory region
- SRAM memory region
- Vector table placement
- Code placement
- Read-only data placement
- Data placement
- BSS placement
- Initial stack address
- ELF entry point

The ELF entry point is explicitly configured as `Reset_Handler`.

## Build System

The project uses the ARM GNU Toolchain and Make.

### Build Firmware

```bash
make
```

### Clean Build Artifacts

```bash
make clean
```

### Generated Files

```text
build/
├── firmware.elf
├── firmware.bin
├── firmware.map
└── object files
```

The ELF file contains symbols and debugging information.

The binary file contains the raw firmware image.

The map file provides detailed linker information about memory placement and symbols.

## Debugging and Inspection

The ELF firmware contains debug information and can be inspected using GDB.

Start GDB:

```bash
arm-none-eabi-gdb build/firmware.elf
```

Useful inspection tools:

```bash
arm-none-eabi-readelf
arm-none-eabi-nm
arm-none-eabi-objdump
arm-none-eabi-size
```

### Example ELF Inspection

```bash
arm-none-eabi-readelf -h build/firmware.elf
```

### Symbol Inspection

```bash
arm-none-eabi-nm -n build/firmware.elf
```

### Disassembly

```bash
arm-none-eabi-objdump -d build/firmware.elf
```

### Memory Usage

```bash
arm-none-eabi-size build/firmware.elf
```

## Firmware Demonstration

The integrated firmware demonstrates interaction between multiple bare-metal drivers.

### Current Demo

- System initialization
- USART1 command interface
- GPIO LED control
- TIM2 periodic interrupt
- EXTI0 interrupt
- NVIC interrupt configuration
- UART status reporting

### UART Commands

```text
HELP
LED ON
LED OFF
LED TOGGLE
STATUS
IRQ
```

### Example

```text
========================================
 Bare-Metal STM32F411 Driver Library
 Final Firmware Demo
========================================
System: 16 MHz HSI
UART: USART1 @ 115200 baud
TIM2: 1 second interrupt
EXTI0: PA0 interrupt
Type HELP for commands.
>
```

## Testing and Verification

The project has been verified through static firmware and build-level testing.

### Build Verification

The firmware is compiled using:

- ARM GCC
- `-Wall`
- `-Wextra`
- Freestanding compilation
- Custom linker script
- Custom startup code

The current firmware builds without compiler, assembler, or linker errors.

### ELF Verification

The firmware ELF has been inspected for:

- ARM architecture
- Cortex-M4-compatible configuration
- Vector table placement
- Reset handler
- Main function
- Interrupt handler symbols
- Stack address
- Flash/RAM sections
- Correct ELF entry point

### Register Address Verification

The compiled ELF was inspected to verify that the expected STM32F411 peripheral addresses are present.

Examples:

```text
GPIOA   0x40020000
RCC     0x40023800
USART1  0x40011000
TIM2    0x40000000
```

### Memory Usage

Current firmware usage:

```text
Flash:
    5020 bytes

RAM:
    36 bytes
```

The debug sections present in the ELF are not part of the raw firmware image.

### Hardware Verification

Physical peripheral runtime verification requires:

- STM32F411RE hardware
- Compatible debug probe
- UART connection for serial testing

The current development environment verifies firmware structure, compilation, ELF contents, register mappings, and debugging information without claiming physical STM32 peripheral execution.

## Virtual Development Environment

The project uses QEMU and GDB as part of the development workflow.

The firmware is built specifically for the STM32F411xE target.

QEMU can be used for ARM Cortex-M experimentation and debugging, but the selected QEMU machine must actually emulate the required STM32 peripheral hardware before peripheral-level runtime behavior can be claimed.

Therefore, QEMU-based execution should not be treated as proof of STM32F411 peripheral behavior unless an appropriate F411-compatible machine model is available.

## Hardware Portability

The driver architecture separates application code from low-level peripheral register access.

The main hardware-specific elements are:

- STM32 peripheral base addresses
- Register layouts
- Interrupt vector assignments
- GPIO alternate-function mappings
- RCC clock configuration
- Timer clock configuration
- MCU-specific memory layout

The driver APIs can be reused on other Cortex-M devices only after adapting the corresponding register definitions and MCU-specific hardware mappings.

The current implementation targets the STM32F411xE family.

## Known Limitations

The following areas are intentionally limited in the current version:

- System clock configuration currently uses the STM32F411 reset-state 16 MHz HSI clock.
- PLL/HSE clock configuration has not yet been implemented.
- Timer clock handling will be expanded when the clock-tree layer is implemented.
- Startup code currently provides the vector table and reset flow but does not yet perform full `.data` copying and `.bss` zero initialization.
- Comprehensive runtime parameter validation is not implemented for every public driver API.
- Physical STM32F411 hardware testing remains pending.
- QEMU peripheral-level verification is limited by available STM32 machine models.

## Project Structure

```text
BareMetalDrivers/
├── build/
├── drivers/
│   ├── exti.c
│   ├── gpio.c
│   ├── nvic.c
│   ├── rcc.c
│   ├── system.c
│   ├── systick.c
│   ├── timer.c
│   └── uart.c
├── include/
│   ├── bit_utils.h
│   ├── exti.h
│   ├── gpio.h
│   ├── memory_map.h
│   ├── nvic.h
│   ├── platform.h
│   ├── rcc.h
│   ├── system.h
│   ├── systick.h
│   ├── timer.h
│   ├── uart.h
│   └── usart.h
├── linker/
│   └── linker.ld
├── startup/
│   └── startup.s
├── main.c
├── Makefile
└── README.md
```

## Development Environment

- Embedded C
- ARM GNU Toolchain
- Make
- GDB
- QEMU
- VS Code
- Git/GitHub

## Project Status

The project currently contains:

- Custom Cortex-M4 startup code
- Custom linker script
- Register-level STM32F411 peripheral definitions
- RCC driver
- GPIO driver
- USART/UART driver
- SysTick driver
- TIM2 driver
- NVIC driver
- EXTI driver
- Integrated interrupt-driven firmware demo
- ELF and memory inspection workflow
- Documentation for build, testing, and hardware portability

The next stage is final repository cleanup, final testing, release preparation, and project documentation refinement.