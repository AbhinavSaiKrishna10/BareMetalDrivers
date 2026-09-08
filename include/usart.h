#ifndef USART_H
#define USART_H

#include <stdint.h>

#define USART1_BASE  0x40011000UL
#define USART2_BASE  0x40004400UL
#define USART6_BASE  0x40011400UL

#define USART_SR_OFFSET    0x00UL
#define USART_DR_OFFSET    0x04UL
#define USART_BRR_OFFSET   0x08UL
#define USART_CR1_OFFSET   0x0CUL
#define USART_CR2_OFFSET   0x10UL
#define USART_CR3_OFFSET   0x14UL
#define USART_GTPR_OFFSET  0x18UL

typedef struct
{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;

} USART_TypeDef;

#define USART1 ((USART_TypeDef *)USART1_BASE)
#define USART2 ((USART_TypeDef *)USART2_BASE)
#define USART6 ((USART_TypeDef *)USART6_BASE)

#endif /* USART_H */