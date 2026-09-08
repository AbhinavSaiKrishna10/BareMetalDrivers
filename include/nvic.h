#ifndef NVIC_H
#define NVIC_H

#include <stdint.h>

/*----------------------------------------------------------
 * NVIC Base Address
 *---------------------------------------------------------*/

#define NVIC_BASE  0xE000E100UL

/*----------------------------------------------------------
 * NVIC Register Structure
 *---------------------------------------------------------*/

typedef struct
{
    volatile uint32_t ISER[8];       /* 0x000 */
    uint32_t RESERVED0[24];          /* 0x020 - 0x07C */

    volatile uint32_t ICER[8];       /* 0x080 */
    uint32_t RESERVED1[24];          /* 0x0A0 - 0x0FC */

    volatile uint32_t ISPR[8];       /* 0x100 */
    uint32_t RESERVED2[24];          /* 0x120 - 0x17C */

    volatile uint32_t ICPR[8];       /* 0x180 */
    uint32_t RESERVED3[24];          /* 0x1A0 - 0x1FC */

    volatile uint32_t IABR[8];       /* 0x200 */
    uint32_t RESERVED4[56];          /* 0x220 - 0x2FC */

    volatile uint8_t  IPR[240];      /* 0x300 */

} NVIC_TypeDef;

/*----------------------------------------------------------
 * NVIC Peripheral Instance
 *---------------------------------------------------------*/

#define NVIC  ((NVIC_TypeDef *)NVIC_BASE)

/*----------------------------------------------------------
 * SCB Base Address
 *---------------------------------------------------------*/

#define SCB_BASE  0xE000ED00UL

/*----------------------------------------------------------
 * SCB Register Structure
 *---------------------------------------------------------*/

typedef struct
{
    volatile uint32_t CPUID;         /* 0x00 */
    volatile uint32_t ICSR;          /* 0x04 */
    volatile uint32_t VTOR;          /* 0x08 */
    volatile uint32_t AIRCR;         /* 0x0C */
    volatile uint32_t SCR;           /* 0x10 */
    volatile uint32_t CCR;           /* 0x14 */
    volatile uint32_t SHPR1;         /* 0x18 */
    volatile uint32_t SHPR2;         /* 0x1C */
    volatile uint32_t SHPR3;         /* 0x20 */
    volatile uint32_t SHCSR;         /* 0x24 */
    volatile uint32_t CFSR;          /* 0x28 */
    volatile uint32_t HFSR;          /* 0x2C */
    volatile uint32_t DFSR;          /* 0x30 */
    volatile uint32_t MMFAR;         /* 0x34 */
    volatile uint32_t BFAR;          /* 0x38 */
    volatile uint32_t AFSR;          /* 0x3C */

} SCB_TypeDef;

/*----------------------------------------------------------
 * SCB Peripheral Instance
 *---------------------------------------------------------*/

#define SCB  ((SCB_TypeDef *)SCB_BASE)

/*----------------------------------------------------------
 * NVIC Driver API
 *---------------------------------------------------------*/

void NVIC_EnableIRQ(uint8_t irq_number);

void NVIC_DisableIRQ(uint8_t irq_number);

void NVIC_SetPendingIRQ(uint8_t irq_number);

void NVIC_ClearPendingIRQ(uint8_t irq_number);

void NVIC_SetPriority(uint8_t irq_number,
                      uint8_t priority);

#endif /* NVIC_H */