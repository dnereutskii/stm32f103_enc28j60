#include "enc28j60.h"
#include <stm32f1xx.h>


/*
 * SPI
 */

uint8_t enc28j60_current_bank = 0;
uint16_t enc28j60_rxrdpt = 0;

#define enc28j60_select()	GPIOB->BSRR = GPIO_BSRR_BR12
#define enc28j60_release()	GPIOB->BSRR = GPIO_BSRR_BS12

uint8_t enc28j60_rxtx(uint8_t data)
{
    while(!(SPI2->SR & SPI_SR_TXE)){}	/*wait for empty Tx buffer*/
	enc28j60_select();	/*activate Chip Select*/
    SPI2->DR = data;	/*sent data*/ 
    while(!(SPI2->SR & SPI_SR_RXNE)){}	/*wait for answer*/
    data = SPI2->DR;	/*read data*/  
	enc28j60_release();	/*deactivate Chip Select*/   
    return data;		/*return data*/
}

#define enc28j60_rx() enc28j60_rxtx(0xff)
#define enc28j60_tx(data) enc28j60_rxtx(data)

// Generic SPI read command
uint8_t enc28j60_read_op(uint8_t cmd, uint8_t adr)
{
	uint8_t data;

	enc28j60_select();
	enc28j60_tx(cmd | (adr & ENC28J60_ADDR_MASK));
	if(adr & 0x80) // throw out dummy byte 
		enc28j60_rx(); // when reading MII/MAC register
	data = enc28j60_rx();
	enc28j60_release();
	return data;
}

// Generic SPI write command
void enc28j60_write_op(uint8_t cmd, uint8_t adr, uint8_t data)
{
	enc28j60_select();
	enc28j60_tx(cmd | (adr & ENC28J60_ADDR_MASK));
	enc28j60_tx(data);
	enc28j60_release();
}

// Initiate software reset
void enc28j60_soft_reset()
{
	enc28j60_select();
	enc28j60_tx(ENC28J60_SPI_SC);
	enc28j60_release();
	
	enc28j60_current_bank = 0;
	// _delay_ms(1); // Wait until device initializes
	for(uint32_t i = 0; i < 1000000; i++){}
}


/*
 * Memory access
 */

// Set register bank
void enc28j60_set_bank(uint8_t adr)
{
	uint8_t bank;

	if( (adr & ENC28J60_ADDR_MASK) < ENC28J60_COMMON_CR )
	{
		bank = (adr >> 5) & 0x03; //BSEL1|BSEL0=0x03
		if(bank != enc28j60_current_bank)
		{
			enc28j60_write_op(ENC28J60_SPI_BFC, ECON1, 0x03);
			enc28j60_write_op(ENC28J60_SPI_BFS, ECON1, bank);
			enc28j60_current_bank = bank;
		}
	}
}

// Read register
uint8_t enc28j60_rcr(uint8_t adr)
{
	enc28j60_set_bank(adr);
	return enc28j60_read_op(ENC28J60_SPI_RCR, adr);
}

// Read register pair
uint16_t enc28j60_rcr16(uint8_t adr)
{
	enc28j60_set_bank(adr);
	return enc28j60_read_op(ENC28J60_SPI_RCR, adr) |
		(enc28j60_read_op(ENC28J60_SPI_RCR, adr+1) << 8);
}

// Write register
void enc28j60_wcr(uint8_t adr, uint8_t arg)
{
	enc28j60_set_bank(adr);
	enc28j60_write_op(ENC28J60_SPI_WCR, adr, arg);
}

// Write register pair
void enc28j60_wcr16(uint8_t adr, uint16_t arg)
{
	enc28j60_set_bank(adr);
	enc28j60_write_op(ENC28J60_SPI_WCR, adr, arg);
	enc28j60_write_op(ENC28J60_SPI_WCR, adr+1, arg>>8);
}

// Clear bits in register (reg &= ~mask)
void enc28j60_bfc(uint8_t adr, uint8_t mask)
{
	enc28j60_set_bank(adr);
	enc28j60_write_op(ENC28J60_SPI_BFC, adr, mask);
}

// Set bits in register (reg |= mask)
void enc28j60_bfs(uint8_t adr, uint8_t mask)
{
	enc28j60_set_bank(adr);
	enc28j60_write_op(ENC28J60_SPI_BFS, adr, mask);
}

// Read Rx/Tx buffer (at ERDPT)
void enc28j60_read_buffer(uint8_t *buf, uint16_t len)
{
	enc28j60_select();
	enc28j60_tx(ENC28J60_SPI_RBM);
	while(len--)
		*(buf++) = enc28j60_rx();
	enc28j60_release();
}

// Write Rx/Tx buffer (at EWRPT)
void enc28j60_write_buffer(uint8_t *buf, uint16_t len)
{
	enc28j60_select();
	enc28j60_tx(ENC28J60_SPI_WBM);
	while(len--){enc28j60_tx(*(buf++));}
	enc28j60_release();
}

// Read PHY register
uint16_t enc28j60_read_phy(uint8_t adr)
{
	enc28j60_wcr(MIREGADR, adr);
	enc28j60_bfs(MICMD, MICMD_MIIRD);
	while(enc28j60_rcr(MISTAT) & MISTAT_BUSY){}
	enc28j60_bfc(MICMD, MICMD_MIIRD);
	return enc28j60_rcr16(MIRD);
}

// Write PHY register
void enc28j60_write_phy(uint8_t adr, uint16_t data)
{
	enc28j60_wcr(MIREGADR, adr);
	enc28j60_wcr16(MIWR, data);
	while(enc28j60_rcr(MISTAT) & MISTAT_BUSY){}
}

static void enc28j60_init_spi(void)
{
	/*GPIO setting*/
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN); 	/*PORTB clock enabling*/
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);	/*AFIO clock enabling*/
	/*CS pin*/
	MODIFY_REG(GPIOB->CRH, GPIO_CRH_MODE12_Msk, GPIO_CRH_MODE12);	/*50MHz output mode*/
	MODIFY_REG(GPIOB->CRH, GPIO_CRH_CNF12_Msk, ~GPIO_CRH_CNF12);	/*General push-pull*/	
	/*SCK pin*/
	MODIFY_REG(GPIOB->CRH, GPIO_CRH_MODE13_Msk, GPIO_CRH_MODE13);	/*50MHz output mode*/
	MODIFY_REG(GPIOB->CRH, GPIO_CRH_CNF13_Msk, GPIO_CRH_CNF13_1);	/*AF push-pull*/
	/*MISO pin*/
	MODIFY_REG(GPIOB->CRH, GPIO_CRH_MODE14_Msk, ~GPIO_CRH_MODE14);	/*input mode*/
	MODIFY_REG(GPIOB->CRH, GPIO_CRH_CNF14_Msk, GPIO_CRH_MODE14_0);	/*Input floating*/	
	/*MOSI pin*/
	MODIFY_REG(GPIOB->CRH, GPIO_CRH_MODE15_Msk, GPIO_CRH_MODE15);	/*50MHz output mode*/
	MODIFY_REG(GPIOB->CRH, GPIO_CRH_CNF15_Msk, GPIO_CRH_CNF15_1);	/*AF push-pull*/

	/*SPI setting*/
	SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);	/*SPI2 clock enabling*/
	/*CR1 setting*/
	SET_BIT(SPI2->CR1, SPI_CR1_MSTR|SPI_CR1_SPE);
	/*CR2 setting*/
}

/*
 * Init & packet Rx/Tx
 */

void enc28j60_init(uint8_t *macadr)
{
	// Initialize SPI
	enc28j60_init_spi();
	enc28j60_release();

	// Reset ENC28J60
	enc28j60_soft_reset();

	// Setup Rx/Tx buffer
	enc28j60_wcr16(ERXST, ENC28J60_RXSTART);
	enc28j60_wcr16(ERXRDPT, ENC28J60_RXSTART);
	enc28j60_wcr16(ERXND, ENC28J60_RXEND);
	enc28j60_rxrdpt = ENC28J60_RXSTART;

	// Setup MAC
	enc28j60_wcr(MACON1, MACON1_TXPAUS| // Enable flow control
		MACON1_RXPAUS|MACON1_MARXEN); // Enable MAC Rx
	// enc28j60_wcr(MACON2, 0); // Clear reset
	enc28j60_wcr(MACON3, MACON3_PADCFG0| // Enable padding,
		MACON3_TXCRCEN|MACON3_FRMLNEN|MACON3_FULDPX); // Enable crc & frame len chk
	enc28j60_wcr16(MAMXFL, ENC28J60_MAXFRAME);
	enc28j60_wcr(MABBIPG, 0x15); // Set inter-frame gap
	enc28j60_wcr(MAIPGL, 0x12);
	enc28j60_wcr(MAIPGH, 0x0c);
	enc28j60_wcr(MAADR6, macadr[0]); // Set MAC address
	enc28j60_wcr(MAADR5, macadr[1]);
	enc28j60_wcr(MAADR4, macadr[2]);
	enc28j60_wcr(MAADR3, macadr[3]);
	enc28j60_wcr(MAADR2, macadr[4]);
	enc28j60_wcr(MAADR1, macadr[5]);

	// Setup PHY
	enc28j60_write_phy(PHCON1, PHCON1_PDPXMD); // Force full-duplex mode
	enc28j60_write_phy(PHCON2, PHCON2_HDLDIS); // Disable loopback
	enc28j60_write_phy(PHLCON, PHLCON_LACFG2| // Configure LED ctrl
		PHLCON_LBCFG2|PHLCON_LBCFG1|PHLCON_LBCFG0|
		PHLCON_LFRQ0|PHLCON_STRCH);

	// Enable Rx packets
	enc28j60_bfs(ECON1, ECON1_RXEN);
}

void enc28j60_send_packet(uint8_t *data, uint16_t len)
{
	while(enc28j60_rcr(ECON1) & ECON1_TXRTS)
	{
		// TXRTS may not clear - ENC28J60 bug. We must reset
		// transmit logic in cause of Tx error
		if(enc28j60_rcr(EIR) & EIR_TXERIF)
		{
			enc28j60_bfs(ECON1, ECON1_TXRST);
			enc28j60_bfc(ECON1, ECON1_TXRST);
		}
	}

	enc28j60_wcr16(EWRPT, ENC28J60_TXSTART);
	enc28j60_write_buffer((uint8_t*)"\x00", 1);
	enc28j60_write_buffer(data, len);

	enc28j60_wcr16(ETXST, ENC28J60_TXSTART);
	enc28j60_wcr16(ETXND, ENC28J60_TXSTART + len);

	enc28j60_bfs(ECON1, ECON1_TXRTS); // Request packet send
}

uint16_t enc28j60_recv_packet(uint8_t *buf, uint16_t buflen)
{
	uint16_t len = 0, rxlen, status, temp;

	if(enc28j60_rcr(EPKTCNT))
	{
		enc28j60_wcr16(ERDPT, enc28j60_rxrdpt);

		enc28j60_read_buffer((void*)&enc28j60_rxrdpt, sizeof(enc28j60_rxrdpt));
		enc28j60_read_buffer((void*)&rxlen, sizeof(rxlen));
		enc28j60_read_buffer((void*)&status, sizeof(status));

		if(status & 0x80) //success
		{
			len = rxlen - 4; //throw out crc
			if(len > buflen) len = buflen;
			enc28j60_read_buffer(buf, len);	
		}

		// Set Rx read pointer to next packet
		temp = (enc28j60_rxrdpt - 1) & ENC28J60_BUFEND;
		enc28j60_wcr16(ERXRDPT, temp);

		// Decrement packet counter
		enc28j60_bfs(ECON2, ECON2_PKTDEC);
	}

	return len;
}
