#include "gpio.h"
#include "timer.h"
#include "uart.h"
#include "nvic.h"
#include "exti.h"
#include "system.h"

/*----------------------------------------------------------
 * Command Interface
 *---------------------------------------------------------*/

#define COMMAND_BUFFER_SIZE  32U

static char command_buffer[COMMAND_BUFFER_SIZE];
static uint32_t command_index = 0U;

/*----------------------------------------------------------
 * TIM2 Interrupt Service Routine
 *---------------------------------------------------------*/

void TIM2_IRQHandler(void)
{
    if (TIM2_IsUpdateEvent())
    {
        /*
         * Clear the timer interrupt condition.
         */
        TIM2_Reset();

        /*
         * Toggle LED.
         */
        GPIO_TogglePin(GPIOA, 5);

        /*
         * Report timer event.
         */
        UART_SendString("\r\n[TIM2] 1 second elapsed\r\n");
        UART_SendString("> ");
    }
}

/*----------------------------------------------------------
 * EXTI0 Interrupt Service Routine
 *---------------------------------------------------------*/

void EXTI0_IRQHandler(void)
{
    if (EXTI_IsPending(0U))
    {
        /*
         * Clear EXTI0 pending condition.
         */
        EXTI_ClearPending(0U);

        /*
         * Toggle LED.
         */
        GPIO_TogglePin(GPIOA, 5);

        /*
         * Report interrupt event.
         */
        UART_SendString("\r\n[EXTI0] Interrupt received\r\n");
        UART_SendString("> ");
    }
}

/*----------------------------------------------------------
 * String Comparison
 *---------------------------------------------------------*/

static uint8_t String_Equals(const char *first,
                             const char *second)
{
    uint32_t index = 0U;

    while ((first[index] != '\0') &&
           (second[index] != '\0'))
    {
        if (first[index] != second[index])
        {
            return 0U;
        }

        index++;
    }

    if ((first[index] == '\0') &&
        (second[index] == '\0'))
    {
        return 1U;
    }

    return 0U;
}

/*----------------------------------------------------------
 * Command Processing
 *---------------------------------------------------------*/

static void Process_Command(const char *command)
{
    if (String_Equals(command, "HELP"))
    {
        UART_SendString("\r\nAvailable commands:\r\n");
        UART_SendString("  HELP       - Show available commands\r\n");
        UART_SendString("  LED ON     - Turn LED on\r\n");
        UART_SendString("  LED OFF    - Turn LED off\r\n");
        UART_SendString("  LED TOGGLE - Toggle LED\r\n");
        UART_SendString("  STATUS     - Show system status\r\n");
        UART_SendString("  IRQ        - Trigger EXTI0 interrupt\r\n");
    }
    else if (String_Equals(command, "LED ON"))
    {
        GPIO_WritePin(GPIOA, 5, GPIO_PIN_HIGH);
        UART_SendString("\r\nLED: ON\r\n");
    }
    else if (String_Equals(command, "LED OFF"))
    {
        GPIO_WritePin(GPIOA, 5, GPIO_PIN_LOW);
        UART_SendString("\r\nLED: OFF\r\n");
    }
    else if (String_Equals(command, "LED TOGGLE"))
    {
        GPIO_TogglePin(GPIOA, 5);
        UART_SendString("\r\nLED toggled\r\n");
    }
    else if (String_Equals(command, "STATUS"))
    {
        UART_SendString("\r\nSystem Status:\r\n");
        UART_SendString("  MCU: STM32F411xE\r\n");
        UART_SendString("  Clock: 16 MHz HSI\r\n");
        UART_SendString("  UART: USART1\r\n");
        UART_SendString("  Baud: 115200\r\n");
        UART_SendString("  TIM2: 1 second period\r\n");
        UART_SendString("  TIM2 IRQ: 28\r\n");
        UART_SendString("  EXTI0 IRQ: 6\r\n");
    }
    else if (String_Equals(command, "IRQ"))
    {
        /*
         * Generate an EXTI0 interrupt through
         * the software interrupt mechanism.
         */
        EXTI_SoftwareTrigger(0U);

        UART_SendString("\r\nEXTI0 software trigger requested\r\n");
    }
    else if (command[0] != '\0')
    {
        UART_SendString("\r\nUnknown command\r\n");
        UART_SendString("Type HELP for available commands.\r\n");
    }
}

/*----------------------------------------------------------
 * UART Command Input
 *---------------------------------------------------------*/

static void UART_ProcessCommandInput(void)
{
    uint8_t received_byte;

    received_byte = UART_ReceiveByte();

    /*
     * Process Enter.
     */
    if ((received_byte == '\r') ||
        (received_byte == '\n'))
    {
        command_buffer[command_index] = '\0';

        Process_Command(command_buffer);

        command_index = 0U;

        UART_SendString("\r\n> ");

        return;
    }

    /*
     * Process Backspace.
     */
    if ((received_byte == '\b') ||
        (received_byte == 127U))
    {
        if (command_index > 0U)
        {
            command_index--;

            UART_SendString("\b \b");
        }

        return;
    }

    /*
     * Store printable characters.
     */
    if ((received_byte >= 32U) &&
        (received_byte <= 126U))
    {
        if (command_index < (COMMAND_BUFFER_SIZE - 1U))
        {
            command_buffer[command_index] =
                (char)received_byte;

            command_index++;

            /*
             * Echo received character.
             */
            UART_SendByte(received_byte);
        }
        else
        {
            UART_SendString("\r\nCommand too long\r\n");

            command_index = 0U;

            UART_SendString("> ");
        }
    }
}

/*----------------------------------------------------------
 * Main
 *---------------------------------------------------------*/

int main(void)
{
    /*
     * ------------------------------------------------------
     * 1. System initialization
     * ------------------------------------------------------
     */
    System_Init();

    /*
     * ------------------------------------------------------
     * 2. UART initialization
     * ------------------------------------------------------
     */
    UART_Init(115200U);

    /*
     * ------------------------------------------------------
     * 3. GPIO initialization
     * ------------------------------------------------------
     *
     * PA5 -> LED output
     */
    GPIO_Init(GPIOA, 5, GPIO_MODE_OUTPUT);

    GPIO_SetPull(GPIOA,
                 5,
                 GPIO_PULL_NONE);

    GPIO_SetOutputType(GPIOA,
                       5,
                       GPIO_OUTPUT_PUSH_PULL);

    GPIO_SetSpeed(GPIOA,
                  5,
                  GPIO_SPEED_HIGH);

    /*
     * PA0 -> EXTI0 input
     */
    GPIO_Init(GPIOA, 0, GPIO_MODE_INPUT);

    GPIO_SetPull(GPIOA,
                 0,
                 GPIO_PULL_DOWN);

    /*
     * ------------------------------------------------------
     * 4. EXTI initialization
     * ------------------------------------------------------
     *
     * EXTI0 <- PA0
     * Trigger: rising edge
     */
    EXTI_Init(0U,
              EXTI_PORT_A,
              EXTI_TRIGGER_RISING);

    /*
     * ------------------------------------------------------
     * 5. TIM2 initialization
     * ------------------------------------------------------
     *
     * TIM2 clock = 16 MHz
     *
     * Prescaler = 15999
     * Counter frequency = 1 kHz
     *
     * ARR = 999
     * Update frequency = 1 Hz
     *
     * Therefore TIM2 interrupt occurs
     * approximately once per second.
     */
    TIM2_Init(16000000U,
              15999U,
              999U);

    /*
     * ------------------------------------------------------
     * 6. Enable TIM2 interrupt
     * ------------------------------------------------------
     */
    TIM2_EnableUpdateInterrupt();

    /*
     * ------------------------------------------------------
     * 7. Configure NVIC
     * ------------------------------------------------------
     *
     * EXTI0 -> IRQ6
     * TIM2  -> IRQ28
     */
    NVIC_SetPriority(6U, 1U);
    NVIC_SetPriority(28U, 2U);

    NVIC_EnableIRQ(6U);
    NVIC_EnableIRQ(28U);

    /*
     * ------------------------------------------------------
     * 8. Enable global interrupts
     * ------------------------------------------------------
     */
    __asm volatile ("cpsie i");

    /*
     * ------------------------------------------------------
     * 9. Start TIM2
     * ------------------------------------------------------
     */
    TIM2_Start();

    /*
     * ------------------------------------------------------
     * 10. Firmware startup message
     * ------------------------------------------------------
     */
    UART_SendString("\r\n");
    UART_SendString("========================================\r\n");
    UART_SendString(" Bare-Metal STM32F411 Driver Library\r\n");
    UART_SendString(" Final Firmware Demo\r\n");
    UART_SendString("========================================\r\n");
    UART_SendString("System: 16 MHz HSI\r\n");
    UART_SendString("UART: USART1 @ 115200 baud\r\n");
    UART_SendString("TIM2: 1 second interrupt\r\n");
    UART_SendString("EXTI0: PA0 interrupt\r\n");
    UART_SendString("Type HELP for commands.\r\n");
    UART_SendString("> ");

    /*
     * ------------------------------------------------------
     * 11. Main application loop
     * ------------------------------------------------------
     */
    while (1)
    {
        UART_ProcessCommandInput();
    }
}