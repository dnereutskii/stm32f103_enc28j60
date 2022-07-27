#include "stm32f1xx.h"
#include "enc28j60_spi.h"
#include "enc28j60.h"

static uint8_t enc28j60_current_bank = 0;
static uint16_t enc28j60_rxrdpt = 0;


/**
  * @brief: Generic SPI read command
  *
  * @param cmd: SPI commandS:
  *				ENC28J60_SPI_RCR
  * @param adr: Main registers
  * 
  * @retval data from a main register	
  */
static uint8_t enc28j60_read_op(uint8_t cmd, uint8_t adr)
{
	uint8_t data;

	ENC28J60_SPI_CS_SELECT();
	ENC28J60_SPI_WRITE_BYTE(cmd | (adr & ENC28J60_ADDR_MASK));
	if (adr & ENC28J60_MII_MAC)/*throw dummy byte out*/
	{ 
		ENC28J60_SPI_READ_BYTE();/*when reading MII/MAC register*/
	}
	data = ENC28J60_SPI_READ_BYTE();
	ENC28J60_SPI_CS_RELEASE();
	return data;
}


/**
  * @brief Generic SPI write command
  *
  * @param cmd  SPI Commands:
  *				ENC28J60_SPI_BFC
  *				ENC28J60_SPI_BFS
  *				ENC28J60_SPI_WCR
  * @param adr  Main register address
  * @param data Data to be written to a main register
  * 
  * @retval None	
  */
static void enc28j60_write_op(uint8_t cmd, uint8_t adr, uint8_t data)
{
	ENC28J60_SPI_CS_SELECT();
	ENC28J60_SPI_WRITE_BYTE(cmd | (adr & ENC28J60_ADDR_MASK));
	ENC28J60_SPI_WRITE_BYTE(data);
	ENC28J60_SPI_CS_RELEASE();
}

// Initiate software reset
void enc28j60_soft_reset()
{
	ENC28J60_SPI_CS_SELECT();
	ENC28J60_SPI_WRITE_BYTE(ENC28J60_SPI_SRC);
	ENC28J60_SPI_CS_RELEASE();
	
	enc28j60_current_bank = 0;

	for (uint32_t i = 0; i < 1000000; i++){}
}


/*
 * Memory access
 */


/**
  * @brief Set register bank by extracting it from main register address 
  *
  * @param adr  Main register address
  * 
  * @retval None	
  */
void enc28j60_set_bank(uint8_t adr)
{
	uint8_t bank;

	if( (adr & ENC28J60_ADDR_MASK) < ENC28J60_COMMON_CR )
	{
		bank = (adr >> 5) & ENC28J60_BANK_SEL_MASK;
		if(bank != enc28j60_current_bank)
		{
			enc28j60_write_op(ENC28J60_SPI_BFC, ECON1, 0x03);
			enc28j60_write_op(ENC28J60_SPI_BFS, ECON1, bank);
			enc28j60_current_bank = bank;
		}
	}
}


/**
  * @brief Read Control Register
  *
  * @param adr Main register address
  * 
  * @retval Main register value	
  */
uint8_t enc28j60_rcr(uint8_t adr)
{
	enc28j60_set_bank(adr);
	return enc28j60_read_op(ENC28J60_SPI_RCR, adr);
}


/**
  * @brief Read register pair
  *
  * @param adr Main register address
  * 
  * @retval Main register value	
  */
uint16_t enc28j60_rcr16(uint8_t adr)
{
    enc28j60_set_bank(adr);
    return enc28j60_read_op(ENC28J60_SPI_RCR, adr) |
        (enc28j60_read_op(ENC28J60_SPI_RCR, adr + 1) << 8);
}


/**
  * @brief Write register
  *
  * @param adr Main register address
  * @param arg Data to be written
  * 
  * @retval None
  */
void enc28j60_wcr(uint8_t adr, uint8_t arg)
{
	enc28j60_set_bank(adr);
	enc28j60_write_op(ENC28J60_SPI_WCR, adr, arg);
}


/**
  * @brief Write register pair
  *
  * @param adr Main register address
  * @param arg Data to be written
  * 
  * @retval None
  */
void enc28j60_wcr16(uint8_t adr, uint16_t arg)
{
	enc28j60_set_bank(adr);
	enc28j60_write_op(ENC28J60_SPI_WCR, adr, (uint8_t) arg);
	enc28j60_write_op(ENC28J60_SPI_WCR, adr + 1, (uint8_t) (arg >> 8));
}


/**
  * @brief Clear bits in ETH control register (reg &= ~mask)
  *
  * @param adr ETH register address
  * @param mask Bit mask
  * 
  * @retval None
  */
void enc28j60_bfc(uint8_t adr, uint8_t mask)
{
	enc28j60_set_bank(adr);
	enc28j60_write_op(ENC28J60_SPI_BFC, adr, mask);
}

 
/**
  * @brief Set bits in register (reg |= mask)
  *
  * @param adr ETH register address
  * @param mask Bit mask
  * 
  * @retval None
  */
void enc28j60_bfs(uint8_t adr, uint8_t mask)
{
	enc28j60_set_bank(adr);
	enc28j60_write_op(ENC28J60_SPI_BFS, adr, mask);
}


/**
  * @brief Clear bits in MII or MAC registers (reg &= ~mask)
  *
  * @param adr MAC or MII register address
  * @param mask Bit mask
  * 
  * @retval None
  */
void enc28j60_bfc_mac_mii(uint8_t adr, uint8_t mask)
{
    uint8_t data;
	enc28j60_set_bank(adr);
    data = enc28j60_read_op(ENC28J60_SPI_RCR, adr);
    data &= ~mask;
	enc28j60_write_op(ENC28J60_SPI_WCR, adr, data);
}


/**
  * @brief Set bits in MII or MAC registers (reg |= mask)
  *
  * @param adr MAC or MII register address
  * @param mask Bit mask
  * 
  * @retval None
  */
void enc28j60_bfs_mac_mii(uint8_t adr, uint8_t mask)
{
    uint8_t data;
	enc28j60_set_bank(adr);
    data = enc28j60_read_op(ENC28J60_SPI_RCR, adr);
    data |= mask;
	enc28j60_write_op(ENC28J60_SPI_WCR, adr, data);
}


/**
  * @brief Read Rx/Tx buffer (at ERDPT)
  *
  * @param buf User buffer to be filled 
  * @param len Data length
  * 
  * @retval None
  */
void enc28j60_read_buffer(uint8_t *buf, uint16_t len)
{
	ENC28J60_SPI_CS_SELECT();
	ENC28J60_SPI_WRITE_BYTE(ENC28J60_SPI_RBM);
	while (len)
	{
        *buf = ENC28J60_SPI_READ_BYTE();
        buf++;
        len--;
	}
	ENC28J60_SPI_CS_RELEASE();
}


/**
  * @brief Write Rx/Tx buffer (at EWRPT)
  *
  * @param buf User buffer to be filled 
  * @param len Data length
  * 
  * @retval None
  */
void enc28j60_write_buffer(uint8_t *buf, uint16_t len)
{
    ENC28J60_SPI_CS_SELECT();
    ENC28J60_SPI_WRITE_BYTE(ENC28J60_SPI_WBM);
	while (len)
    {
        ENC28J60_SPI_WRITE_BYTE(*buf);
        buf++;
        len--;
    }
    ENC28J60_SPI_CS_RELEASE();
}


/**
  * @brief Read PHY register
  *
  * @param adr PHY address
  * 
  * @retval PHY register value
  */
uint16_t enc28j60_read_phy(uint8_t adr)
{
	enc28j60_wcr(MIREGADR, adr);
	/*enc28j60_bfs(MICMD, MICMD_MIIRD);/*warning: p29 sub 4.2.5 of datasheet*/
    enc28j60_bfs_mac_mii(MICMD, MICMD_MIIRD);
	while (enc28j60_rcr(MISTAT) & MISTAT_BUSY){}
	/*enc28j60_bfc(MICMD, MICMD_MIIRD);/*warning: p29 sub 4.2.5 of datasheet*/
	enc28j60_bfc_mac_mii(MICMD, MICMD_MIIRD);
	return enc28j60_rcr16(MIRD);
}


/**
  * @brief Write PHY register
  *
  * @param adr  PHY address
  * @param data Data to be written
  * 
  * @retval None
  */
void enc28j60_write_phy(uint8_t adr, uint16_t data)
{
    enc28j60_wcr(MIREGADR, adr);
    enc28j60_wcr16(MIWR, data);
    while (enc28j60_rcr(MISTAT) & MISTAT_BUSY){}
}


/*
 * Init & packet Rx/Tx
 */
void enc28j60_init(uint8_t *macadr)
{
	enc28j60_spi_init();/*Initialize SPI*/
	enc28j60_soft_reset();/*Reset ENC28J60*/

	/*Setup Rx/Tx buffer*/
	enc28j60_wcr16(ERXST, ENC28J60_RXSTART);
	enc28j60_wcr16(ERXRDPT, ENC28J60_RXSTART);
	enc28j60_wcr16(ERXND, ENC28J60_RXEND);
	enc28j60_rxrdpt = ENC28J60_RXSTART;

	/*Setup MAC*/
	enc28j60_wcr(MACON1, 
                 MACON1_TXPAUS |  /*Enable flow control*/
		         MACON1_RXPAUS |
                 MACON1_MARXEN    /*Enable MAC Rx*/
    ); 
	// enc28j60_wcr(MACON2, 0); /*Clear reset /*reserved rev. E*/
	enc28j60_wcr(MACON3, 
                 MACON3_PADCFG0 |   /*Padding to 60 bytes and CRC*/
		         MACON3_TXCRCEN |   /*MAC will append a valid CRC*/
                 MACON3_FRMLNEN |   /*Type/length field will be checked*/
                 MACON3_FULDPX      /*Full-Duplex mode PDPXMD bit must also be set*/
    ); 

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
	enc28j60_write_phy(PHLCON, 
                       PHLCON_LACFG2 | // Configure LED ctrl
		               PHLCON_LBCFG2 |
                       PHLCON_LBCFG1 |
                       PHLCON_LBCFG0 |
		               PHLCON_LFRQ0  |
                       PHLCON_STRCH
    );

	
	enc28j60_bfs(ECON1, ECON1_RXEN);/*Enable Rx packets*/
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
