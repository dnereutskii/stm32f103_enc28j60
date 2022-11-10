#include "stm32f1xx.h"
#include "buart.h"

uint8_t uart_rxrd;
uint8_t uart_rxwr;
uint8_t uart_rx[UART_BUFSIZE];

uint8_t uart_txrd;
uint8_t uart_txwr;
uint8_t uart_tx[UART_BUFSIZE];


USART1_IRQHandler(USART_RXC_vect)
{
	uint8_t byte;
	uint8_t wr = (uart_rxwr + 1) & UART_BUFEND;
	byte = UDR;
	if(wr != uart_rxrd)
	{
		uart_rx[uart_rxwr] = byte;
		uart_rxwr = wr;
	}
}

USART1_IRQHandler(USART_UDRE_vect)
{
	uint8_t rd = uart_txrd;
	if(rd != uart_txwr)
	{
		UDR = uart_tx[rd];
		uart_txrd = (rd+1) & UART_BUFEND;
		return;
	}
	UCSRB &= ~(1<<UDRIE);
}

uint8_t uart_rx_count()
{
	return (uart_rxwr-uart_rxrd) & UART_BUFEND;
}

uint8_t uart_read()
{
	uint8_t rd = uart_rxrd;
	uint8_t byte;
	if(rd != uart_rxwr)
	{
		byte = uart_rx[rd];
		uart_rxrd = (rd+1) & UART_BUFEND;
		return byte;
	}
	return 0;
}

void uart_write(uint8_t byte)
{
	uint8_t wr = (uart_txwr+1) & UART_BUFEND;
	if(wr != uart_txrd)
	{
		uart_tx[uart_txwr] = byte;
		uart_txwr = wr;
		UCSRB |= (1<<UDRIE);
	}
}

void uart_init(void)
{

}
