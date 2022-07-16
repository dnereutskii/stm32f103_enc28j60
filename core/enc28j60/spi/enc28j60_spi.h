#ifndef ENC28J60_SPI_H
#define ENC28J60_SPI_H

#define ENC28J60_CS_TAKE()          GPIOB->BSRR = GPIO_BSRR_BR12
#define ENC28J60_CS_RELEASE()       GPIOB->BSRR = GPIO_BSRR_BS12
#define ENC28J60_READ_DATA()        enc28j60_spi_rw_data(0x00)
#define ENC28J60_WRITE_DATA(DATA)   enc28j60_spi_rw_data(DATA)

void enc28j60_spi_init(void);
uint8_t enc28j60_spi_rw_data(uint8_t data);
void enc28j60_spi_enable(void);
void enc28j60_spi_disable(void);

#endif /*ENC28J60_SPI_H*/