#include "systick.h"

#define SYSTICK_TICKS_PER_MS  1000U

void SysTick_Init(uint32_t clock_hz)
{
    uint32_t reload_value;

    /*
     * Calculate number of clock cycles required
     * for a 1 millisecond period.
     *
     * ticks = clock / 1000
     */
    reload_value = (clock_hz / SYSTICK_TICKS_PER_MS) - 1U;

    /*
     * Disable SysTick before configuration.
     */
    SYST_CSR = 0U;

    /*
     * Set reload value.
     */
    SYST_RVR = reload_value;

    /*
     * Clear current counter value.
     */
    SYST_CVR = 0U;

    /*
     * Enable SysTick.
     *
     * CLKSOURCE = 1
     * Use processor clock.
     *
     * TICKINT = 0
     * No interrupt.
     *
     * ENABLE = 1
     * Start counter.
     */
    SYST_CSR = SYST_CSR_CLKSOURCE |
               SYST_CSR_ENABLE;
}


void SysTick_DelayMs(uint32_t milliseconds)
{
    uint32_t elapsed_ms;

    elapsed_ms = 0U;

    /*
     * Wait for the requested number of
     * SysTick periods.
     */
    while (elapsed_ms < milliseconds)
    {
        /*
         * COUNTFLAG becomes 1 when the counter
         * reaches zero.
         */
        while ((SYST_CSR & SYST_CSR_COUNTFLAG) == 0U)
        {
        }

        elapsed_ms++;
    }
}