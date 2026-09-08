#include "timer.h"
#include "rcc.h"

#define TIM_CR1_CEN       (1U << 0)
#define TIM_DIER_UIE      (1U << 0)
#define TIM_EGR_UG        (1U << 0)
#define TIM_SR_UIF        (1U << 0)

void TIM2_Init(uint32_t timer_clock_hz,
               uint32_t prescaler,
               uint32_t auto_reload)
{
    RCC_EnablePeripheral(RCC_TIM2);

    TIM2->CR1 &= ~TIM_CR1_CEN;

    TIM2->PSC = prescaler;
    TIM2->ARR = auto_reload;
    TIM2->CNT = 0U;

    TIM2->EGR = TIM_EGR_UG;

    TIM2->SR &= ~TIM_SR_UIF;

    (void)timer_clock_hz;
}

void TIM2_Start(void)
{
    TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM2_Stop(void)
{
    TIM2->CR1 &= ~TIM_CR1_CEN;
}

void TIM2_Reset(void)
{
    TIM2->CNT = 0U;
    TIM2->SR &= ~TIM_SR_UIF;
}

uint8_t TIM2_IsUpdateEvent(void)
{
    if ((TIM2->SR & TIM_SR_UIF) != 0U)
    {
        return 1U;
    }

    return 0U;
}

void TIM2_EnableUpdateInterrupt(void)
{
    TIM2->DIER |= TIM_DIER_UIE;
}