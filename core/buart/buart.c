#include "stm32f1xx.h"
#include "buart.h"

/**
 * @brief GPIO initialization for USART2
 * 
 * @note PA2 - TX
 *       PA3 - RX
 * 
 * @param None
 * @return None
 */
static void gpio_init(void);

/**
 * @brief USART2 module initialization
 * 
 * @param [in] baudrate USART2 baudrate
 * @return None
 */
static void usart2_init(uint16_t baudrate);

/**
 * @brief USART2 enable
 * 
 * @param None
 * @return None
 */
static void usart2_enable(void);

static uint8_t uart_rxrd;               /*!< Index where we get data */
static uint8_t uart_rxwr;               /*!< Index where interrupt appends data */
static uint8_t uart_rx[UART_BUFSIZE];   /*!< Receive buffer */

static uint8_t uart_txrd;               /*!< Index where interrupt gets data */
static uint8_t uart_txwr;               /*!< Index where we append data */
static uint8_t uart_tx[UART_BUFSIZE];   /*!< Transmit buffer */

void USART2_IRQHandler(void)//USART_RXC_vect
{
    if (USART2->SR & USART_SR_TXE) /* It is cleared by a write to the USART_DR register */
    {
        uint8_t rd = uart_txrd;
        if(rd != uart_txwr) /* There are data to be sent */
        {
            USART2->DR = uart_tx[rd];
            uart_txrd = (rd + 1) & UART_BUFEND;
            return;
        }
        // UCSRB &= ~(1<<UDRIE);
        USART2->CR1 &= ~USART_CR1_TXEIE;  /* TXE interrupt disable */
    }

    if (USART2->SR & USART_SR_RXNE) /* It is cleared by a read to the USART_DR register */
    {
        uint8_t byte;
        uint8_t wr = (uart_rxwr + 1) & UART_BUFEND;
        byte = USART2->DR;
        if(wr != uart_rxrd)
        {
            uart_rx[uart_rxwr] = byte;
            uart_rxwr = wr;
        }
    }
}

uint8_t uart_rx_count(void)
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

void uart_write_byte(uint8_t byte)
{
	uint8_t wr = (uart_txwr + 1) & UART_BUFEND; /* Check if buffer over */
	if(wr != uart_txrd) /* anti-rewriting */
	{
		uart_tx[uart_txwr] = byte;
		uart_txwr = wr;
		// UCSRB |= (1<<UDRIE);
        USART2->CR1 |= USART_CR1_TXEIE;  /* TXE interrupt enable */
	}
}

void uart_write_string(const uint8_t *str)
{
    while (*str)
    {
        uart_write_byte(*str);
        str++;
    }
}

void uart_write_data(const uint8_t *array, uint8_t len)
{
    uint8_t i;
    for (i = 0; i < len; i++)
    {
        uart_write_byte(array[i]);
    }
}

void uart_init(uint16_t baudrate)
{
    gpio_init();/* GPIO Init */
    usart2_init(baudrate);/* USART init */
}

static void gpio_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | /* GPIOA clock enable */
                    RCC_APB2ENR_AFIOEN;  /* AF clock enable*/

    GPIOA->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2 |
                    GPIO_CRL_CNF3 | GPIO_CRL_MODE3); /* Clear bits */
    
    GPIOA->CRL |= GPIO_CRL_MODE2 | GPIO_CRL_CNF2_1; /* PA2 - AF output push-pull */
    GPIOA->CRL |= GPIO_CRL_MODE3 | GPIO_CRL_CNF3_1; /* PA3 - AF output push-pull */
}

static void usart2_init(uint16_t baudrate)
{
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN; /* enable USART2 clock */

    USART2->CR1 = 0;                  /* Clear CR1 */
    USART2->CR1 &= ~USART_CR1_M;      /* 1 start bit, 8-bit length */
    USART2->CR1 |= /*USART_CR1_TXEIE |   TXE interrupt enable */
                   USART_CR1_RXNEIE | /* RXNE Interrupt Enable */
                   USART_CR1_TE |     /* Transmitter Enable*/
                   USART_CR1_RE;      /* Receiver Enable*/

    USART2->CR2 &= ~USART_CR2_STOP;   /* 1 stop bit */

    USART2->BRR = baudrate;
    NVIC_EnableIRQ(USART2_IRQn);
    usart2_enable();
}

static void usart2_enable(void)
{
    USART2->CR1 |= USART_CR1_UE;
}