#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "system.h"

#define UART_DEFAULT_BAUD_RATE  115200U
#define UART_DEFAULT_CLOCK_HZ   SYSTEM_CLOCK_HZ

void UART_Init(uint32_t baud_rate);

void UART_SendByte(uint8_t data);

uint8_t UART_ReceiveByte(void);

void UART_SendString(const char *string);

#endif /* UART_H */