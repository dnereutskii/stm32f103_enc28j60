#ifndef ENC28J60_SPI_H
#define ENC28J60_SPI_H

void enc28j60_spi_init(void);
uint8_t enc28j60_spi_rw_data(uint8_t data);

#endif /*ENC28J60_SPI_H*/