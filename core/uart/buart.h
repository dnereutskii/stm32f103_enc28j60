#ifndef BUART_H
#define BUART_H

#define UART_RATE		115200

#define UART_BUFSIZE	128
#define UART_BUFEND		(UART_BUFSIZE-1)

void uart_init();
uint8_t uart_rx_count();
uint8_t uart_read();
void uart_write(uint8_t byte);

#endif /* BUART_H */