#ifndef EXTI_H
#define EXTI_H

#include <stdint.h>

/*----------------------------------------------------------
 * SYSCFG Base Address
 *---------------------------------------------------------*/

#define SYSCFG_BASE  0x40013800UL

/*----------------------------------------------------------
 * SYSCFG Register Offsets
 *---------------------------------------------------------*/

#define SYSCFG_MEMRMP_OFFSET   0x00UL
#define SYSCFG_PMC_OFFSET      0x04UL
#define SYSCFG_EXTICR1_OFFSET  0x08UL
#define SYSCFG_EXTICR2_OFFSET  0x0CUL
#define SYSCFG_EXTICR3_OFFSET  0x10UL
#define SYSCFG_EXTICR4_OFFSET  0x14UL
#define SYSCFG_CMPCR_OFFSET    0x20UL

/*----------------------------------------------------------
 * SYSCFG Register Structure
 *---------------------------------------------------------*/

typedef struct
{
    volatile uint32_t MEMRMP;       /* 0x00 */
    volatile uint32_t PMC;          /* 0x04 */
    volatile uint32_t EXTICR1;      /* 0x08 */
    volatile uint32_t EXTICR2;      /* 0x0C */
    volatile uint32_t EXTICR3;      /* 0x10 */
    volatile uint32_t EXTICR4;      /* 0x14 */
    uint32_t RESERVED0[2];          /* 0x18 - 0x1C */
    volatile uint32_t CMPCR;        /* 0x20 */

} SYSCFG_TypeDef;

#define SYSCFG ((SYSCFG_TypeDef *)SYSCFG_BASE)

/*----------------------------------------------------------
 * EXTI Base Address
 *---------------------------------------------------------*/

#define EXTI_BASE  0x40013C00UL

/*----------------------------------------------------------
 * EXTI Register Structure
 *---------------------------------------------------------*/

typedef struct
{
    volatile uint32_t IMR;          /* 0x00 */
    volatile uint32_t EMR;          /* 0x04 */
    volatile uint32_t RTSR;         /* 0x08 */
    volatile uint32_t FTSR;         /* 0x0C */
    volatile uint32_t SWIER;        /* 0x10 */
    volatile uint32_t PR;           /* 0x14 */

} EXTI_TypeDef;

#define EXTI ((EXTI_TypeDef *)EXTI_BASE)

/*----------------------------------------------------------
 * EXTI Trigger Configuration
 *---------------------------------------------------------*/

typedef enum
{
    EXTI_TRIGGER_RISING = 0U,
    EXTI_TRIGGER_FALLING,
    EXTI_TRIGGER_BOTH

} EXTI_Trigger_t;

/*----------------------------------------------------------
 * EXTI GPIO Port Selection
 *---------------------------------------------------------*/

typedef enum
{
    EXTI_PORT_A = 0U,
    EXTI_PORT_B = 1U,
    EXTI_PORT_C = 2U,
    EXTI_PORT_D = 3U,
    EXTI_PORT_E = 4U,
    EXTI_PORT_H = 7U

} EXTI_Port_t;

/*----------------------------------------------------------
 * EXTI Driver API
 *---------------------------------------------------------*/

void EXTI_Init(uint8_t line,
               EXTI_Port_t port,
               EXTI_Trigger_t trigger);

void EXTI_EnableInterrupt(uint8_t line);
void EXTI_DisableInterrupt(uint8_t line);

void EXTI_ClearPending(uint8_t line);
uint8_t EXTI_IsPending(uint8_t line);

void EXTI_SoftwareTrigger(uint8_t line);

#endif /* EXTI_H */