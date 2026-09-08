#include "rcc.h"
#include "bit_utils.h"

void RCC_EnablePeripheral(RCC_Peripheral_t peripheral)
{
    switch (peripheral)
    {
        case RCC_GPIOA:
            SET_BIT(RCC_AHB1ENR, 0);
            break;

        case RCC_GPIOB:
            SET_BIT(RCC_AHB1ENR, 1);
            break;

        case RCC_GPIOC:
            SET_BIT(RCC_AHB1ENR, 2);
            break;

        case RCC_GPIOD:
            SET_BIT(RCC_AHB1ENR, 3);
            break;

        case RCC_GPIOE:
            SET_BIT(RCC_AHB1ENR, 4);
            break;

        case RCC_GPIOH:
            SET_BIT(RCC_AHB1ENR, 7);
            break;

        case RCC_USART1:
            SET_BIT(RCC_APB2ENR, 4);
            break;

        case RCC_USART2:
            SET_BIT(RCC_APB1ENR, 17);
            break;

        case RCC_USART6:
            SET_BIT(RCC_APB2ENR, 5);
            break;

        case RCC_SYSCFG:
            SET_BIT(RCC_APB2ENR, 14);
            break;

        case RCC_TIM2:
            SET_BIT(RCC_APB1ENR, 0);
            break;

        case RCC_TIM3:
            SET_BIT(RCC_APB1ENR, 1);
            break;

        case RCC_TIM4:
            SET_BIT(RCC_APB1ENR, 2);
            break;

        case RCC_TIM5:
            SET_BIT(RCC_APB1ENR, 3);
            break;

        default:
            break;
    }
}