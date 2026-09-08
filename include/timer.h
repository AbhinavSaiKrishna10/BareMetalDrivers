#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/*----------------------------------------------------------
 * Timer Base Addresses
 *---------------------------------------------------------*/

#define TIM2_BASE  0x40000000UL
#define TIM3_BASE  0x40000400UL
#define TIM4_BASE  0x40000800UL
#define TIM5_BASE  0x40000C00UL

/*----------------------------------------------------------
 * Timer Register Structure
 *---------------------------------------------------------*/

typedef struct
{
    volatile uint32_t CR1;       /* 0x00 */
    volatile uint32_t CR2;       /* 0x04 */
    volatile uint32_t SMCR;      /* 0x08 */
    volatile uint32_t DIER;      /* 0x0C */
    volatile uint32_t SR;        /* 0x10 */
    volatile uint32_t EGR;       /* 0x14 */
    volatile uint32_t CCMR1;     /* 0x18 */
    volatile uint32_t CCMR2;     /* 0x1C */
    volatile uint32_t CCER;      /* 0x20 */
    volatile uint32_t CNT;       /* 0x24 */
    volatile uint32_t PSC;       /* 0x28 */
    volatile uint32_t ARR;       /* 0x2C */
    volatile uint32_t RESERVED0; /* 0x30 */
    volatile uint32_t CCR1;      /* 0x34 */
    volatile uint32_t CCR2;      /* 0x38 */
    volatile uint32_t CCR3;      /* 0x3C */
    volatile uint32_t CCR4;      /* 0x40 */
    volatile uint32_t RESERVED1; /* 0x44 */
    volatile uint32_t DCR;       /* 0x48 */
    volatile uint32_t DMAR;      /* 0x4C */
    volatile uint32_t OR;        /* 0x50 */

} TIM_TypeDef;

/*----------------------------------------------------------
 * Timer Peripheral Instances
 *---------------------------------------------------------*/

#define TIM2 ((TIM_TypeDef *)TIM2_BASE)
#define TIM3 ((TIM_TypeDef *)TIM3_BASE)
#define TIM4 ((TIM_TypeDef *)TIM4_BASE)
#define TIM5 ((TIM_TypeDef *)TIM5_BASE)

/*----------------------------------------------------------
 * Timer Driver API
 *---------------------------------------------------------*/

void TIM2_Init(uint32_t timer_clock_hz,
               uint32_t prescaler,
               uint32_t auto_reload);

void TIM2_Start(void);
void TIM2_Stop(void);
void TIM2_Reset(void);
uint8_t TIM2_IsUpdateEvent(void);

void TIM2_EnableUpdateInterrupt(void);

#endif /* TIMER_H */