#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

/*----------------------------------------------------------
 * SysTick Register Addresses
 *---------------------------------------------------------*/

#define SYSTICK_BASE    0xE000E010UL

#define SYST_CSR_OFFSET 0x00UL
#define SYST_RVR_OFFSET 0x04UL
#define SYST_CVR_OFFSET 0x08UL
#define SYST_CALIB_OFFSET 0x0CUL

/*----------------------------------------------------------
 * SysTick Registers
 *---------------------------------------------------------*/

#define SYST_CSR \
    (*(volatile uint32_t *)(SYSTICK_BASE + SYST_CSR_OFFSET))

#define SYST_RVR \
    (*(volatile uint32_t *)(SYSTICK_BASE + SYST_RVR_OFFSET))

#define SYST_CVR \
    (*(volatile uint32_t *)(SYSTICK_BASE + SYST_CVR_OFFSET))

#define SYST_CALIB \
    (*(volatile uint32_t *)(SYSTICK_BASE + SYST_CALIB_OFFSET))

/*----------------------------------------------------------
 * SysTick Control Register Bits
 *---------------------------------------------------------*/

#define SYST_CSR_ENABLE      (1U << 0)
#define SYST_CSR_TICKINT     (1U << 1)
#define SYST_CSR_CLKSOURCE   (1U << 2)
#define SYST_CSR_COUNTFLAG   (1U << 16)

/*----------------------------------------------------------
 * SysTick API
 *---------------------------------------------------------*/

void SysTick_Init(uint32_t clock_hz);

void SysTick_DelayMs(uint32_t milliseconds);

#endif /* SYSTICK_H */