#include "stm32f1xx.h"
#include "enc28j60_spi.h"


void enc28j60_spi_init(void)
{
    RCC->APB2ENR  |= (RCC_APB2ENR_IOPBEN |    /*enable GPIOB clock*/
                      RCC_APB2ENR_AFIOEN);    /*enable AF clock*/

    GPIOB->CRH &= ~(GPIO_CRH_MODE12 | GPIO_CRH_CNF12 |
                    GPIO_CRH_MODE13 | GPIO_CRH_CNF13 |
                    GPIO_CRH_MODE14 | GPIO_CRH_CNF14 |
                    GPIO_CRH_MODE15 | GPIO_CRH_CNF15); /*reset GPIO setting*/

    GPIOB->CRH |= (GPIO_CRH_MODE12);    /*CS: output push-pull*/
    GPIOB->CRH |= (GPIO_CRH_MODE13 |
                   GPIO_CRH_CNF13_1);   /*SCK: AF push-pull*/
    GPIOB->CRH |= (GPIO_CRH_CNF14_0);   /*MISO input floating*/
    GPIOB->CRH |= (GPIO_CRH_MODE15 | 
                   GPIO_CRH_CNF15_1);   /*MOSI: AF push-pull*/

    RCC->APB1ENR |= (RCC_APB1ENR_SPI2EN); /*enable SPI2 clock*/  

    SPI2->CR1 &= ~(SPI_CR1_CPOL);   /*Polarity cls signal CPOL = 0;*/
    SPI2->CR1 &= ~(SPI_CR1_CPHA);   /*Phase cls signal    CPHA = 0;*/
    SPI2->CR1 |= (SPI_CR1_MSTR);    /*Master Mode*/
    SPI2->CR1 |= (SPI_CR1_BR_0);     /*Baud rate = Fpclk / 4 = 9 MHz*/
    SPI2->CR1 &= ~(SPI_CR1_LSBFIRST); /*MSB will be first*/
    SPI2->CR1 |= (SPI_CR1_SSM | 
                  SPI_CR1_SSI);     /*Software slave management */
    SPI2->CR1 &= ~(SPI_CR1_RXONLY); /*full-duplex*/
    SPI2->CR1 &= ~(SPI_CR1_DFF);    /*8 bit data*/
    
    SPI2->CR2 = 0;

    ENC28J60_SPI_CS_RELEASE();
}


void enc28j60_spi_enable(void)
{    
    SPI2->CR1 |= (SPI_CR1_SPE);
}


void enc28j60_spi_disable(void)
{    
    SPI2->CR1 &= ~(SPI_CR1_SPE);
}


uint8_t enc28j60_spi_rw_byte(uint8_t data)
{
    while(!(SPI2->SR & SPI_SR_TXE)) {}/*wait for empty TX buffer*/
    // ENC28J60_SPI_CS_SELECT();/*Chip Select on*/
    SPI2->DR = data;/*send out data*/
    while(!(SPI2->SR & SPI_SR_RXNE)) {}/*wait answer*/
    data = SPI2->DR;/*read our data*/
    // ENC28J60_SPI_CS_RELEASE();/*Chip Select off*/
    return data;/*return what we read*/
}

