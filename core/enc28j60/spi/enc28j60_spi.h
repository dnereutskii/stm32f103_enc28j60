#ifndef ENC28J60_SPI_H
#define ENC28J60_SPI_H

#define ENC28J60_SPI_CS_SELECT()        GPIOB->BSRR = GPIO_BSRR_BR12
#define ENC28J60_SPI_CS_RELEASE()       GPIOB->BSRR = GPIO_BSRR_BS12

#define ENC28J60_SPI_READ_BYTE()        enc28j60_spi_rw_byte(0x00)
#define ENC28J60_SPI_WRITE_BYTE(DATA)   enc28j60_spi_rw_byte(DATA)

void enc28j60_spi_init(void);
uint8_t enc28j60_spi_rw_byte(uint8_t data);
void enc28j60_spi_enable(void);
void enc28j60_spi_disable(void);

#endif /*ENC28J60_SPI_H*/