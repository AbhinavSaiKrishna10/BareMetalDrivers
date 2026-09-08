#include "uart.h"
#include "gpio.h"
#include "rcc.h"
#include "usart.h"

/*
 * Calculate USART baud-rate register value.
 *
 * For STM32F411 USART with oversampling by 16:
 *
 * BRR = Peripheral Clock / Baud Rate
 */
static uint16_t UART_CalculateBRR(uint32_t peripheral_clock,
                                  uint32_t baud_rate)
{
    uint32_t usart_div;

    usart_div = (peripheral_clock + (baud_rate / 2U))
                / baud_rate;

    return (uint16_t)usart_div;
}


void UART_Init(uint32_t baud_rate)
{
    uint16_t brr_value;

    /*
     * Enable GPIOA clock.
     *
     * USART1:
     * PA9  -> TX
     * PA10 -> RX
     */
    RCC_EnablePeripheral(RCC_GPIOA);

    /*
     * Enable USART1 clock.
     */
    RCC_EnablePeripheral(RCC_USART1);

    /*
     * Configure PA9 as Alternate Function.
     */
    GPIO_SetMode(GPIOA, 9, GPIO_MODE_AF);

    /*
     * USART1 uses Alternate Function 7.
     */
    GPIO_SetAlternateFunction(GPIOA, 9, GPIO_AF7);

    /*
     * TX configuration.
     */
    GPIO_SetOutputType(GPIOA,
                       9,
                       GPIO_OUTPUT_PUSH_PULL);

    GPIO_SetPull(GPIOA,
                 9,
                 GPIO_PULL_NONE);

    GPIO_SetSpeed(GPIOA,
                  9,
                  GPIO_SPEED_HIGH);

    /*
     * Configure PA10 as Alternate Function.
     */
    GPIO_SetMode(GPIOA, 10, GPIO_MODE_AF);

    /*
     * USART1 uses Alternate Function 7.
     */
    GPIO_SetAlternateFunction(GPIOA, 10, GPIO_AF7);

    /*
     * RX configuration.
     */
    GPIO_SetPull(GPIOA,
                 10,
                 GPIO_PULL_NONE);

    /*
     * Disable USART1 before configuration.
     */
    USART1->CR1 = 0U;

    /*
     * Calculate baud rate.
     *
     * Current assumption:
     * USART1 peripheral clock = 16 MHz.
     */
    brr_value = UART_CalculateBRR(UART_DEFAULT_CLOCK_HZ,
                                  baud_rate);

    USART1->BRR = brr_value;

    /*
     * Enable transmitter.
     *
     * CR1 bit 3 = TE
     */
    USART1->CR1 |= (1U << 3);

    /*
     * Enable receiver.
     *
     * CR1 bit 2 = RE
     */
    USART1->CR1 |= (1U << 2);

    /*
     * Enable USART.
     *
     * CR1 bit 13 = UE
     */
    USART1->CR1 |= (1U << 13);
}


/*
 * 7.5 — UART Transmit
 *
 * Send one byte through USART1.
 */
void UART_SendByte(uint8_t data)
{
    /*
     * Wait until the transmit data register
     * is empty.
     *
     * SR bit 7 = TXE
     */
    while ((USART1->SR & (1U << 7)) == 0U)
    {
    }

    /*
     * Write the byte to the data register.
     */
    USART1->DR = data;
}


/*
 * 7.6 — UART Receive
 *
 * Receive one byte from USART1.
 */
uint8_t UART_ReceiveByte(void)
{
    /*
     * Wait until received data is available.
     *
     * SR bit 5 = RXNE
     */
    while ((USART1->SR & (1U << 5)) == 0U)
    {
    }

    /*
     * Reading DR retrieves the received byte.
     */
    return (uint8_t)USART1->DR;
}


/*
 * 7.7 — UART String Transmission
 *
 * Send a null-terminated string.
 */
void UART_SendString(const char *string)
{
    /*
     * Continue until the null terminator.
     */
    while (*string != '\0')
    {
        UART_SendByte((uint8_t)*string);

        string++;
    }
}