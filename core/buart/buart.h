#ifndef BUART_H
#define BUART_H

#define UART_RATE		115200

#define UART_BUFSIZE	128
#define UART_BUFEND		(UART_BUFSIZE-1)

#define UART_9600       (uint16_t)0xEA6
#define UART_19200      (uint16_t)0x753
#define UART_115200     (uint16_t)0x139

void uart_init(uint16_t baudrate);
uint8_t uart_rx_count();
uint8_t uart_read();
void uart_write(uint8_t byte);

#endif /* BUART_H */