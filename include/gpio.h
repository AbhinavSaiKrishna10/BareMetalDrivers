#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/*----------------------------------------------------------
 * GPIO Base Addresses
 *---------------------------------------------------------*/

#define GPIOA_BASE  0x40020000UL
#define GPIOB_BASE  0x40020400UL
#define GPIOC_BASE  0x40020800UL
#define GPIOD_BASE  0x40020C00UL
#define GPIOE_BASE  0x40021000UL
#define GPIOH_BASE  0x40021C00UL

/*----------------------------------------------------------
 * GPIO Register Offsets
 *---------------------------------------------------------*/

#define GPIO_MODER_OFFSET    0x00UL
#define GPIO_OTYPER_OFFSET   0x04UL
#define GPIO_OSPEEDR_OFFSET  0x08UL
#define GPIO_PUPDR_OFFSET    0x0CUL
#define GPIO_IDR_OFFSET      0x10UL
#define GPIO_ODR_OFFSET      0x14UL
#define GPIO_BSRR_OFFSET     0x18UL
#define GPIO_LCKR_OFFSET     0x1CUL
#define GPIO_AFRL_OFFSET     0x20UL
#define GPIO_AFRH_OFFSET     0x24UL

/*----------------------------------------------------------
 * GPIO Register Structure
 *---------------------------------------------------------*/

typedef struct
{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;

} GPIO_TypeDef;

/*----------------------------------------------------------
 * GPIO Peripheral Instances
 *---------------------------------------------------------*/

#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef *)GPIOE_BASE)
#define GPIOH ((GPIO_TypeDef *)GPIOH_BASE)

/*----------------------------------------------------------
 * GPIO Modes
 *---------------------------------------------------------*/

typedef enum
{
    GPIO_MODE_INPUT  = 0x00U,
    GPIO_MODE_OUTPUT = 0x01U,
    GPIO_MODE_AF     = 0x02U,
    GPIO_MODE_ANALOG = 0x03U

} GPIO_Mode_t;

/*----------------------------------------------------------
 * GPIO Pin State
 *---------------------------------------------------------*/

typedef enum
{
    GPIO_PIN_LOW  = 0U,
    GPIO_PIN_HIGH = 1U

} GPIO_PinState_t;

/*----------------------------------------------------------
 * GPIO Pull-up / Pull-down
 *---------------------------------------------------------*/

typedef enum
{
    GPIO_PULL_NONE = 0x00U,
    GPIO_PULL_UP   = 0x01U,
    GPIO_PULL_DOWN = 0x02U

} GPIO_Pull_t;

/*----------------------------------------------------------
 * GPIO Output Type
 *---------------------------------------------------------*/

typedef enum
{
    GPIO_OUTPUT_PUSH_PULL  = 0x00U,
    GPIO_OUTPUT_OPEN_DRAIN = 0x01U

} GPIO_OutputType_t;

/*----------------------------------------------------------
 * GPIO Output Speed
 *---------------------------------------------------------*/

typedef enum
{
    GPIO_SPEED_LOW       = 0x00U,
    GPIO_SPEED_MEDIUM    = 0x01U,
    GPIO_SPEED_HIGH      = 0x02U,
    GPIO_SPEED_VERY_HIGH = 0x03U

} GPIO_Speed_t;

/*----------------------------------------------------------
 * GPIO Alternate Function
 *---------------------------------------------------------*/

typedef enum
{
    GPIO_AF0  = 0x00U,
    GPIO_AF1  = 0x01U,
    GPIO_AF2  = 0x02U,
    GPIO_AF3  = 0x03U,
    GPIO_AF4  = 0x04U,
    GPIO_AF5  = 0x05U,
    GPIO_AF6  = 0x06U,
    GPIO_AF7  = 0x07U,
    GPIO_AF8  = 0x08U,
    GPIO_AF9  = 0x09U,
    GPIO_AF10 = 0x0AU,
    GPIO_AF11 = 0x0BU,
    GPIO_AF12 = 0x0CU,
    GPIO_AF13 = 0x0DU,
    GPIO_AF14 = 0x0EU,
    GPIO_AF15 = 0x0FU

} GPIO_AF_t;

/*----------------------------------------------------------
 * GPIO API
 *---------------------------------------------------------*/

void GPIO_SetMode(GPIO_TypeDef *GPIOx,
                  uint8_t pin,
                  GPIO_Mode_t mode);

void GPIO_Init(GPIO_TypeDef *GPIOx,
               uint8_t pin,
               GPIO_Mode_t mode);

void GPIO_WritePin(GPIO_TypeDef *GPIOx,
                   uint8_t pin,
                   GPIO_PinState_t state);

GPIO_PinState_t GPIO_ReadPin(GPIO_TypeDef *GPIOx,
                             uint8_t pin);

void GPIO_TogglePin(GPIO_TypeDef *GPIOx,
                    uint8_t pin);

void GPIO_SetPull(GPIO_TypeDef *GPIOx,
                  uint8_t pin,
                  GPIO_Pull_t pull);

void GPIO_SetOutputType(GPIO_TypeDef *GPIOx,
                        uint8_t pin,
                        GPIO_OutputType_t type);

void GPIO_SetSpeed(GPIO_TypeDef *GPIOx,
                   uint8_t pin,
                   GPIO_Speed_t speed);

void GPIO_SetAlternateFunction(GPIO_TypeDef *GPIOx,
                               uint8_t pin,
                               GPIO_AF_t alternate_function);

#endif /* GPIO_H */