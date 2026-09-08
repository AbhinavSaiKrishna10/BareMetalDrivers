#include "nvic.h"

/*----------------------------------------------------------
 * 9.2 — NVIC Enable / Disable
 *---------------------------------------------------------*/

void NVIC_EnableIRQ(uint8_t irq_number)
{
    uint32_t register_index;
    uint32_t bit_position;

    /*
     * Each ISER register controls 32 IRQs.
     */
    register_index = irq_number / 32U;
    bit_position = irq_number % 32U;

    /*
     * Set the corresponding enable bit.
     */
    NVIC->ISER[register_index] =
        (1U << bit_position);
}


void NVIC_DisableIRQ(uint8_t irq_number)
{
    uint32_t register_index;
    uint32_t bit_position;

    register_index = irq_number / 32U;
    bit_position = irq_number % 32U;

    /*
     * Disable the corresponding IRQ.
     */
    NVIC->ICER[register_index] =
        (1U << bit_position);
}


/*----------------------------------------------------------
 * Pending Interrupt Control
 *---------------------------------------------------------*/

void NVIC_SetPendingIRQ(uint8_t irq_number)
{
    uint32_t register_index;
    uint32_t bit_position;

    register_index = irq_number / 32U;
    bit_position = irq_number % 32U;

    /*
     * Set interrupt pending.
     */
    NVIC->ISPR[register_index] =
        (1U << bit_position);
}


void NVIC_ClearPendingIRQ(uint8_t irq_number)
{
    uint32_t register_index;
    uint32_t bit_position;

    register_index = irq_number / 32U;
    bit_position = irq_number % 32U;

    /*
     * Clear interrupt pending state.
     */
    NVIC->ICPR[register_index] =
        (1U << bit_position);
}


/*----------------------------------------------------------
 * 9.3 — Interrupt Priority
 *---------------------------------------------------------*/

void NVIC_SetPriority(uint8_t irq_number,
                      uint8_t priority)
{
    /*
     * STM32F411 implements 4 priority bits.
     *
     * The priority is stored in the upper
     * four bits of the 8-bit IPR field.
     */
    NVIC->IPR[irq_number] =
        (uint8_t)(priority << 4U);
}