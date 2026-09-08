#include "exti.h"
#include "rcc.h"

void EXTI_Init(uint8_t line,
               EXTI_Port_t port,
               EXTI_Trigger_t trigger)
{
    uint32_t register_index;
    uint32_t position;

    /*
     * Enable SYSCFG peripheral clock.
     */
    RCC_EnablePeripheral(RCC_SYSCFG);

    /*
     * Each SYSCFG_EXTICR register controls
     * four EXTI lines.
     */
    register_index = line / 4U;
    position = (uint32_t)(line % 4U) * 4U;

    /*
     * Select the GPIO port connected to the EXTI line.
     */
    switch (register_index)
    {
        case 0U:
            SYSCFG->EXTICR1 &= ~(0xFU << position);
            SYSCFG->EXTICR1 |= ((uint32_t)port << position);
            break;

        case 1U:
            SYSCFG->EXTICR2 &= ~(0xFU << position);
            SYSCFG->EXTICR2 |= ((uint32_t)port << position);
            break;

        case 2U:
            SYSCFG->EXTICR3 &= ~(0xFU << position);
            SYSCFG->EXTICR3 |= ((uint32_t)port << position);
            break;

        case 3U:
            SYSCFG->EXTICR4 &= ~(0xFU << position);
            SYSCFG->EXTICR4 |= ((uint32_t)port << position);
            break;

        default:
            return;
    }

    /*
     * Disable both edge detectors before
     * configuring the requested trigger.
     */
    EXTI->RTSR &= ~(1U << line);
    EXTI->FTSR &= ~(1U << line);

    switch (trigger)
    {
        case EXTI_TRIGGER_RISING:
            EXTI->RTSR |= (1U << line);
            break;

        case EXTI_TRIGGER_FALLING:
            EXTI->FTSR |= (1U << line);
            break;

        case EXTI_TRIGGER_BOTH:
            EXTI->RTSR |= (1U << line);
            EXTI->FTSR |= (1U << line);
            break;

        default:
            return;
    }

    /*
     * Clear any stale pending request.
     *
     * EXTI_PR is cleared by writing 1 to
     * the corresponding bit.
     */
    EXTI->PR = (1U << line);

    /*
     * Enable interrupt generation for this line.
     */
    EXTI->IMR |= (1U << line);
}

void EXTI_EnableInterrupt(uint8_t line)
{
    EXTI->IMR |= (1U << line);
}

void EXTI_DisableInterrupt(uint8_t line)
{
    EXTI->IMR &= ~(1U << line);
}

void EXTI_ClearPending(uint8_t line)
{
    EXTI->PR = (1U << line);
}

uint8_t EXTI_IsPending(uint8_t line)
{
    if ((EXTI->PR & (1U << line)) != 0U)
    {
        return 1U;
    }

    return 0U;
}

void EXTI_SoftwareTrigger(uint8_t line)
{
    EXTI->SWIER |= (1U << line);
}