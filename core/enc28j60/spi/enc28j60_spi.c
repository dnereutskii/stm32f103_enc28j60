#include "enc28j60_spi.h"
#include "stm32f1xx.h"

#define CS_LOW()  GPIOB->BSRR = GPIO_BSRR_BR10
#define CS_HIGH() GPIOB->BSRR = GPIO_BSRR_BS10

void enc28j60_spi_init(void)
{
//включаем тактирование порта B и альтернативных функций 
RCC->APB2ENR  |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;   
//13(SCK) and 15(MOSI) outputs - AF push pull, 14(MISO) input - Input floating, 10(CS) pin - output, push-pull
GPIOB->CRH &= ~(GPIO_CRH_CNF13_0 | GPIO_CRH_CNF15_0 | GPIO_CRH_CNF10_0);  
GPIOB->CRH |= GPIO_CRH_CNF13_1 | GPIO_CRH_CNF15_1;  	
GPIOB->CRH |= GPIO_CRH_MODE10_0 | GPIO_CRH_MODE13_1 |	GPIO_CRH_MODE15_1;

//turn on SPI2 clock
RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;   

SPI2->CR1 |= SPI_CR1_BR;                //Baud rate = Fpclk/256
SPI2->CR1 &= ~SPI_CR1_CPOL;             //Polarity cls signal CPOL = 0;
SPI2->CR1 &= ~SPI_CR1_CPHA;             //Phase cls signal    CPHA = 0;
SPI2->CR1 |= SPI_CR1_DFF;               //16 bit data
SPI2->CR1 &= ~SPI_CR1_LSBFIRST;         //MSB will be first
SPI2->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;  //Software slave management & Internal slave select
	
SPI2->CR1 |= SPI_CR1_MSTR;              //Mode Master
SPI2->CR1 |= SPI_CR1_SPE;               //Enable SPI2
}

uint8_t enc28j60_spi_rw_data(uint8_t data)
{
    //wait for empty TX buffer
    while(!(SPI2->SR & SPI_SR_TXE));
    //Chip Select on
    CS_LOW();  
     //send out data
    SPI2->DR = data;  
     //wait answer
    while(!(SPI2->SR & SPI_SR_RXNE));
     //read our data
    data = SPI2->DR;  
    //Chip Select off
    CS_HIGH();  
     //return what we read
    return data;  
}

