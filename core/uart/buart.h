#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>

#define UART_RATE		19200

#define UART_BUFSIZE	128
#define UART_BUFEND		(UART_BUFSIZE-1)

void uart_init();
uint8_t uart_rx_count();
uint8_t uart_read();
void uart_write(uint8_t byte);
