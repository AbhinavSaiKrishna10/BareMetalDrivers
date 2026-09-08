#include "system.h"

/*
 * STM32F411 reset state:
 *
 * HSI = 16 MHz
 * HSI selected as SYSCLK
 *
 * Therefore no clock-source switching is
 * required for the initial system configuration.
 */

void System_Init(void)
{
    /*
     * The STM32F411 starts with the 16 MHz
     * HSI oscillator selected as the system clock.
     *
     * Clock configuration will be expanded here
     * when PLL/HSE support is added.
     */
}