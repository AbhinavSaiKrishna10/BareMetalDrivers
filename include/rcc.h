#ifndef RCC_H
#define RCC_H

#include <stdint.h>

/*----------------------------------------------------------
 * RCC Base Address
 *---------------------------------------------------------*/

#define RCC_BASE        0x40023800UL

/*----------------------------------------------------------
 * RCC Register Offsets
 *---------------------------------------------------------*/

#define RCC_CR_OFFSET       0x00UL
#define RCC_PLLCFGR_OFFSET  0x04UL
#define RCC_CFGR_OFFSET     0x08UL
#define RCC_CIR_OFFSET      0x0CUL
#define RCC_AHB1RSTR_OFFSET 0x10UL
#define RCC_AHB2RSTR_OFFSET 0x14UL
#define RCC_AHB1ENR_OFFSET  0x30UL
#define RCC_AHB2ENR_OFFSET  0x34UL
#define RCC_APB1ENR_OFFSET  0x40UL
#define RCC_APB2ENR_OFFSET  0x44UL

/*----------------------------------------------------------
 * RCC Registers
 *---------------------------------------------------------*/

#define RCC_CR       (*(volatile uint32_t *)(RCC_BASE + RCC_CR_OFFSET))
#define RCC_PLLCFGR  (*(volatile uint32_t *)(RCC_BASE + RCC_PLLCFGR_OFFSET))
#define RCC_CFGR     (*(volatile uint32_t *)(RCC_BASE + RCC_CFGR_OFFSET))
#define RCC_CIR      (*(volatile uint32_t *)(RCC_BASE + RCC_CIR_OFFSET))

#define RCC_AHB1RSTR (*(volatile uint32_t *)(RCC_BASE + RCC_AHB1RSTR_OFFSET))
#define RCC_AHB2RSTR (*(volatile uint32_t *)(RCC_BASE + RCC_AHB2RSTR_OFFSET))

#define RCC_AHB1ENR  (*(volatile uint32_t *)(RCC_BASE + RCC_AHB1ENR_OFFSET))
#define RCC_AHB2ENR  (*(volatile uint32_t *)(RCC_BASE + RCC_AHB2ENR_OFFSET))

#define RCC_APB1ENR  (*(volatile uint32_t *)(RCC_BASE + RCC_APB1ENR_OFFSET))
#define RCC_APB2ENR  (*(volatile uint32_t *)(RCC_BASE + RCC_APB2ENR_OFFSET))

/*----------------------------------------------------------
 * RCC Peripheral Identifiers
 *---------------------------------------------------------*/

typedef enum
{
    RCC_GPIOA,
    RCC_GPIOB,
    RCC_GPIOC,
    RCC_GPIOD,
    RCC_GPIOE,
    RCC_GPIOH,

    RCC_USART1,
    RCC_USART2,
    RCC_USART6,

    RCC_SYSCFG,

    RCC_TIM2,
    RCC_TIM3,
    RCC_TIM4,
    RCC_TIM5

} RCC_Peripheral_t;

/*----------------------------------------------------------
 * RCC API
 *---------------------------------------------------------*/

void RCC_EnablePeripheral(RCC_Peripheral_t peripheral);

#endif /* RCC_H */