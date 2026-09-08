/*
 * startup.s
 *
 * Bare-Metal Startup Code
 * Target: STM32F411xE / ARM Cortex-M4
 */

.syntax unified
.cpu cortex-m4
.thumb

.extern main

.global Reset_Handler
.global NMI_Handler
.global HardFault_Handler
.global EXTI0_IRQHandler
.global TIM2_IRQHandler
.global Default_Handler

.section .isr_vector, "a", %progbits

.global g_pfnVectors
.type g_pfnVectors, %object

g_pfnVectors:

    /*------------------------------------------------------
     * Cortex-M4 Core Exception Vectors
     *-----------------------------------------------------*/

    .word _estack
    .word Reset_Handler
    .word NMI_Handler
    .word HardFault_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word Default_Handler
    .word Default_Handler
    .word 0
    .word Default_Handler
    .word Default_Handler

    /*------------------------------------------------------
     * STM32F411 External Interrupt Vectors
     *
     * IRQ 0  -> WWDG
     * IRQ 1  -> EXTI16/PVD
     * IRQ 2  -> EXTI21/TAMP_STAMP
     * IRQ 3  -> EXTI22/RTC_WKUP
     * IRQ 4  -> FLASH
     * IRQ 5  -> RCC
     * IRQ 6  -> EXTI0
     *-----------------------------------------------------*/

    .word Default_Handler       /* IRQ0  - WWDG */
    .word Default_Handler       /* IRQ1  - EXTI16/PVD */
    .word Default_Handler       /* IRQ2  - EXTI21/TAMP_STAMP */
    .word Default_Handler       /* IRQ3  - EXTI22/RTC_WKUP */
    .word Default_Handler       /* IRQ4  - FLASH */
    .word Default_Handler       /* IRQ5  - RCC */
    .word EXTI0_IRQHandler      /* IRQ6  - EXTI0 */

    /* IRQ7 - IRQ51 */

    .word Default_Handler       /* IRQ7  */
    .word Default_Handler       /* IRQ8  */
    .word Default_Handler       /* IRQ9  */
    .word Default_Handler       /* IRQ10 */
    .word Default_Handler       /* IRQ11 */
    .word Default_Handler       /* IRQ12 */
    .word Default_Handler       /* IRQ13 */
    .word Default_Handler       /* IRQ14 */
    .word Default_Handler       /* IRQ15 */
    .word Default_Handler       /* IRQ16 */
    .word Default_Handler       /* IRQ17 */
    .word Default_Handler       /* IRQ18 */
    .word Default_Handler       /* IRQ19 */
    .word Default_Handler       /* IRQ20 */
    .word Default_Handler       /* IRQ21 */
    .word Default_Handler       /* IRQ22 */
    .word Default_Handler       /* IRQ23 */
    .word Default_Handler       /* IRQ24 */
    .word Default_Handler       /* IRQ25 */
    .word Default_Handler       /* IRQ26 */
    .word Default_Handler       /* IRQ27 */
    .word TIM2_IRQHandler       /* IRQ28 - TIM2 */
    .word Default_Handler       /* IRQ29 */
    .word Default_Handler       /* IRQ30 */
    .word Default_Handler       /* IRQ31 */
    .word Default_Handler       /* IRQ32 */
    .word Default_Handler       /* IRQ33 */
    .word Default_Handler       /* IRQ34 */
    .word Default_Handler       /* IRQ35 */
    .word Default_Handler       /* IRQ36 */
    .word Default_Handler       /* IRQ37 */
    .word Default_Handler       /* IRQ38 */
    .word Default_Handler       /* IRQ39 */
    .word Default_Handler       /* IRQ40 */
    .word Default_Handler       /* IRQ41 */
    .word Default_Handler       /* IRQ42 */
    .word Default_Handler       /* IRQ43 */
    .word Default_Handler       /* IRQ44 */
    .word Default_Handler       /* IRQ45 */
    .word Default_Handler       /* IRQ46 */
    .word Default_Handler       /* IRQ47 */
    .word Default_Handler       /* IRQ48 */
    .word Default_Handler       /* IRQ49 */
    .word Default_Handler       /* IRQ50 */
    .word Default_Handler       /* IRQ51 */


/*----------------------------------------------------------
 * Reset Handler
 *---------------------------------------------------------*/

.section .text.Reset_Handler, "ax", %progbits

.type Reset_Handler, %function

Reset_Handler:

    bl main

1:
    b 1b


/*----------------------------------------------------------
 * Default Handler
 *---------------------------------------------------------*/

.section .text.Default_Handler, "ax", %progbits

.type Default_Handler, %function

Default_Handler:

1:
    b 1b


/*----------------------------------------------------------
 * NMI Handler
 *---------------------------------------------------------*/

.section .text.NMI_Handler, "ax", %progbits

.type NMI_Handler, %function

NMI_Handler:

    b Default_Handler


/*----------------------------------------------------------
 * HardFault Handler
 *---------------------------------------------------------*/

.section .text.HardFault_Handler, "ax", %progbits

.type HardFault_Handler, %function

HardFault_Handler:

    b Default_Handler
    