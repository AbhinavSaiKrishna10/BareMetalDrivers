#include "gpio.h"
#include "rcc.h"

/*----------------------------------------------------------
 * GPIO Set Mode
 *---------------------------------------------------------*/

void GPIO_SetMode(GPIO_TypeDef *GPIOx,
                  uint8_t pin,
                  GPIO_Mode_t mode)
{
    uint32_t position = (uint32_t)pin * 2U;

    /* Clear the existing 2-bit mode configuration */
    GPIOx->MODER &= ~(0x3U << position);

    /* Set the new mode */
    GPIOx->MODER |= ((uint32_t)mode << position);
}

/*----------------------------------------------------------
 * GPIO Initialization
 *---------------------------------------------------------*/

void GPIO_Init(GPIO_TypeDef *GPIOx,
               uint8_t pin,
               GPIO_Mode_t mode)
{
    /* Enable GPIO peripheral clock */
    if (GPIOx == GPIOA)
    {
        RCC_EnablePeripheral(RCC_GPIOA);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnablePeripheral(RCC_GPIOB);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnablePeripheral(RCC_GPIOC);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_EnablePeripheral(RCC_GPIOD);
    }
    else if (GPIOx == GPIOE)
    {
        RCC_EnablePeripheral(RCC_GPIOE);
    }
    else if (GPIOx == GPIOH)
    {
        RCC_EnablePeripheral(RCC_GPIOH);
    }

    /* Configure GPIO pin mode */
    GPIO_SetMode(GPIOx, pin, mode);
}

/*----------------------------------------------------------
 * GPIO Write Pin
 *---------------------------------------------------------*/

void GPIO_WritePin(GPIO_TypeDef *GPIOx,
                   uint8_t pin,
                   GPIO_PinState_t state)
{
    if (state == GPIO_PIN_HIGH)
    {
        GPIOx->BSRR = (1U << pin);
    }
    else
    {
        GPIOx->BSRR = (1U << (pin + 16U));
    }
}

/*----------------------------------------------------------
 * GPIO Read Pin
 *---------------------------------------------------------*/

GPIO_PinState_t GPIO_ReadPin(GPIO_TypeDef *GPIOx,
                             uint8_t pin)
{
    return (GPIOx->IDR >> pin) & 1U;
}

/*----------------------------------------------------------
 * GPIO Toggle Pin
 *---------------------------------------------------------*/

void GPIO_TogglePin(GPIO_TypeDef *GPIOx,
                    uint8_t pin)
{
    GPIOx->ODR ^= (1U << pin);
}

/*----------------------------------------------------------
 * GPIO Set Pull-up / Pull-down
 *---------------------------------------------------------*/

void GPIO_SetPull(GPIO_TypeDef *GPIOx,
                  uint8_t pin,
                  GPIO_Pull_t pull)
{
    uint32_t position = (uint32_t)pin * 2U;

    /* Clear the existing 2-bit pull configuration */
    GPIOx->PUPDR &= ~(0x3U << position);

    /* Set the new pull configuration */
    GPIOx->PUPDR |= ((uint32_t)pull << position);
}

/*----------------------------------------------------------
 * GPIO Set Output Type
 *---------------------------------------------------------*/

void GPIO_SetOutputType(GPIO_TypeDef *GPIOx,
                        uint8_t pin,
                        GPIO_OutputType_t type)
{
    if (type == GPIO_OUTPUT_OPEN_DRAIN)
    {
        GPIOx->OTYPER |= (1U << pin);
    }
    else
    {
        GPIOx->OTYPER &= ~(1U << pin);
    }
}

/*----------------------------------------------------------
 * GPIO Set Output Speed
 *---------------------------------------------------------*/

void GPIO_SetSpeed(GPIO_TypeDef *GPIOx,
                   uint8_t pin,
                   GPIO_Speed_t speed)
{
    uint32_t position = (uint32_t)pin * 2U;

    /* Clear the existing 2-bit speed configuration */
    GPIOx->OSPEEDR &= ~(0x3U << position);

    /* Set the new speed */
    GPIOx->OSPEEDR |= ((uint32_t)speed << position);
}

/*----------------------------------------------------------
 * GPIO Set Alternate Function
 *---------------------------------------------------------*/

void GPIO_SetAlternateFunction(GPIO_TypeDef *GPIOx,
                               uint8_t pin,
                               GPIO_AF_t alternate_function)
{
    uint32_t position;

    if (pin < 8U)
    {
        position = (uint32_t)pin * 4U;

        /* Clear existing alternate function */
        GPIOx->AFRL &= ~(0xFU << position);

        /* Set new alternate function */
        GPIOx->AFRL |= ((uint32_t)alternate_function << position);
    }
    else
    {
        position = ((uint32_t)pin - 8U) * 4U;

        /* Clear existing alternate function */
        GPIOx->AFRH &= ~(0xFU << position);

        /* Set new alternate function */
        GPIOx->AFRH |= ((uint32_t)alternate_function << position);
    }
}