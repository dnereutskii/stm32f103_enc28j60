#ifndef BUART_H
#define BUART_H

#define UART_RATE_9600       (uint16_t)0xEA6
#define UART_RATE_19200      (uint16_t)0x753
#define UART_RATE_115200     (uint16_t)0x139

#define UART_BUFSIZE         128
#define UART_BUFEND          (UART_BUFSIZE-1)

void uart_init(uint16_t baudrate);

/**
 * @brief Get unread data status 
 * 
 * @param None
 * @return Count of unread data from RX buffer
 */
uint8_t uart_rx_count();
uint8_t uart_read();
void uart_write_byte(uint8_t byte);
void uart_write_string(const uint8_t *str);
void uart_write_data(const uint8_t *array, uint8_t len);

#endif /* BUART_H */