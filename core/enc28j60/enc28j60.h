#ifndef ENC28J60_H
#define ENC28J60_H

#define ENC28J60_BUFSIZE	0x2000
#define ENC28J60_RXSIZE		0x1A00
#define ENC28J60_BUFEND		(ENC28J60_BUFSIZE - 1)

#define ENC28J60_MAXFRAME	1518

#define ENC28J60_RXSTART    0
#define ENC28J60_RXEND      (ENC28J60_RXSIZE - 1)
#define ENC28J60_TXSTART    ENC28J60_RXSIZE

#define ENC28J60_MII_MAC    0x80    /*MII and MAC register label*/

/*
 * SPI Instruction Set
 */
#define ENC28J60_SPI_RCR	0x00    /*Read Control Register*/
#define ENC28J60_SPI_RBM	0x3A    /*Read Buffer Memory*/
#define ENC28J60_SPI_WCR	0x40    /*Write Control Register*/
#define ENC28J60_SPI_WBM	0x7A    /*Write Buffer Memory*/
#define ENC28J60_SPI_BFS	0x80    /*Bit Field Set*/
#define ENC28J60_SPI_BFC	0xA0    /*Bit Field Clear*/
#define ENC28J60_SPI_SRC	0xFF    /*System Reset Command*/

#define ENC28J60_ADDR_MASK	0x1F    /*Mask for main register addresses*/
#define ENC28J60_BANK_MASK  0x03    /*Bank select mask: BSEL1|BSEL0*/
#define ENC28J60_COMMON_CR	0x1B

/*
 * Main registers Bank 0
 */
 
#define EIE 				0x1B
#define EIR 				0x1C
#define ESTAT 				0x1D
#define ECON2 				0x1E
#define ECON1 				0x1F


// Buffer read pointer
#define ERDPTL 				0x00
#define ERDPTH 				0x01
#define ERDPT				ERDPTL

/*Write Pointer*/
#define EWRPTL 				0x02    /*Write Pointer Low Byte*/
#define EWRPTH 				0x03    /*Write Pointer High Byte*/
#define EWRPT				EWRPTL

// Tx packet start pointer
#define ETXSTL 				0x04
#define ETXSTH 				0x05
#define ETXST				ETXSTL

// Tx packet end pointer
#define ETXNDL 				0x06
#define ETXNDH 				0x07
#define ETXND				ETXNDL

// Rx FIFO start pointer
#define ERXSTL 				0x08
#define ERXSTH 				0x09
#define ERXST				ERXSTL

// Rx FIFO end pointer
#define ERXNDL 				0x0A
#define ERXNDH 				0x0B
#define ERXND				ERXNDL

// Rx FIFO read pointer
#define ERXRDPTL 			0x0C
#define ERXRDPTH 			0x0D
#define ERXRDPT				ERXRDPTL

// Rx FIFO write pointer
#define ERXWRPTL 			0x0E
#define ERXWRPTH 			0x0F
#define ERXWRPT				ERXWRPTL

// DMA source block start pointer
#define EDMASTL 			0x10
#define EDMASTH 			0x11
#define EDMAST				EDMASTL

// DMA source block end pointer
#define EDMANDL 			0x12
#define EDMANDH 			0x13
#define EDMAND				EDMANDL

// DMA destination pointer
#define EDMADSTL 			0x14
#define EDMADSTH 			0x15
#define	EDMADST				EDMADSTL

// DMA checksum
#define EDMACSL 			0x16
#define EDMACSH 			0x17
#define EDMACS				EDMACSL

/*
 * Main registers Bank 1
 */

// Hash table registers 
#define EHT0 				(0x00 | 0x20)
#define EHT1 				(0x01 | 0x20)
#define EHT2 				(0x02 | 0x20)
#define EHT3 				(0x03 | 0x20)
#define EHT4 				(0x04 | 0x20)
#define EHT5 				(0x05 | 0x20)
#define EHT6 				(0x06 | 0x20)
#define EHT7 				(0x07 | 0x20)

// Pattern match registers
#define EPMM0 				(0x08 | 0x20)
#define EPMM1 				(0x09 | 0x20)
#define EPMM2 				(0x0A | 0x20)
#define EPMM3 				(0x0B | 0x20)
#define EPMM4 				(0x0C | 0x20)
#define EPMM5 				(0x0D | 0x20)
#define EPMM6 				(0x0E | 0x20)
#define EPMM7 				(0x0F | 0x20)
#define EPMCSL 				(0x10 | 0x20)
#define EPMCSH 				(0x11 | 0x20)
#define EPMOL 				(0x14 | 0x20)
#define EPMOH 				(0x15 | 0x20)

// Wake-on-LAN interrupt registers
// #define EWOLIE 				(0x16 | 0x20)   /*reserved rev. E*/
// #define EWOLIR 				(0x17 | 0x20)   /*reserved rev. E*/

// Receive filters mask
#define ERXFCON 			(0x18 | 0x20)

// Packet counter
#define EPKTCNT 			(0x19 | 0x20)

/*
 * Main registers Bank 2
 */

// MAC control registers
#define MACON1 				(0x00 | 0x40 | ENC28J60_MII_MAC)
// #define MACON2 				(0x01 | 0x40 | 0x80)    /*reserved rev. E*/
#define MACON3 				(0x02 | 0x40 | ENC28J60_MII_MAC)
#define MACON4 				(0x03 | 0x40 | ENC28J60_MII_MAC)

// MAC Back-to-back gap
#define MABBIPG 			(0x04 | 0x40 | ENC28J60_MII_MAC)

// MAC Non back-to-back gap
#define MAIPGL 				(0x06 | 0x40 | ENC28J60_MII_MAC)
#define MAIPGH 				(0x07 | 0x40 | ENC28J60_MII_MAC)

// Collision window & rexmit timer
#define MACLCON1 			(0x08 | 0x40 | ENC28J60_MII_MAC)
#define MACLCON2 			(0x09 | 0x40 | ENC28J60_MII_MAC)

// Max frame length
#define MAMXFLL 			(0x0A | 0x40 | ENC28J60_MII_MAC)
#define MAMXFLH 			(0x0B | 0x40 | ENC28J60_MII_MAC)
#define MAMXFL				(MAMXFLL)

// MAC-PHY support register
// #define MAPHSUP 			(0x0D | 0x40 | 0x80)    /*reserved rev. E*/
// #define MICON 			(0x11 | 0x40 | 0x80)    /*reserved rev. E*/

// MII registers
#define MICMD 				(0x12 | 0x40 | ENC28J60_MII_MAC)
#define MIREGADR 			(0x14 | 0x40 | ENC28J60_MII_MAC)

#define MIWRL 				(0x16 | 0x40 | ENC28J60_MII_MAC)
#define MIWRH 				(0x17 | 0x40 | ENC28J60_MII_MAC)
#define MIWR				(MIWRL)

#define MIRDL 				(0x18 | 0x40 | ENC28J60_MII_MAC)
#define MIRDH 				(0x19 | 0x40 | ENC28J60_MII_MAC)
#define MIRD				(MIRDL)

/*
 * Main registers Bank 3
 */

// MAC Address
#define MAADR5 				(0x00 | 0x60 | ENC28J60_MII_MAC)
#define MAADR6 				(0x01 | 0x60 | ENC28J60_MII_MAC)
#define MAADR3 				(0x02 | 0x60 | ENC28J60_MII_MAC)
#define MAADR4 				(0x03 | 0x60 | ENC28J60_MII_MAC)
#define MAADR1 				(0x04 | 0x60 | ENC28J60_MII_MAC)
#define MAADR2 				(0x05 | 0x60 | ENC28J60_MII_MAC)

// Built-in self-test
#define EBSTSD 				(0x06 | 0x60)
#define EBSTCON 			(0x07 | 0x60)
#define EBSTCSL 			(0x08 | 0x60)
#define EBSTCSH 			(0x09 | 0x60)
#define MISTAT 				(0x0A | 0x60 | ENC28J60_MII_MAC)

// Revision ID
#define EREVID 				(0x12 | 0x60)

// Clock output control register
#define ECOCON 				(0x15 | 0x60)

// Flow control registers
#define EFLOCON 			(0x17 | 0x60)
#define EPAUSL 				(0x18 | 0x60)
#define EPAUSH 				(0x19 | 0x60)

/*
 * PHY registers
 */

#define PHCON1 				0x00
#define PHSTAT1 			0x01
#define PHID1 				0x02
#define PHID2 				0x03
#define PHCON2 				0x10
#define PHSTAT2 			0x11
#define PHIE 				0x12
#define PHIR 				0x13
#define PHLCON 				0x14

/*
 * Bits
 */

// EIE
#define EIE_INTIE			0x80
#define EIE_PKTIE			0x40
#define EIE_DMAIE			0x20
#define EIE_LINKIE			0x10
#define EIE_TXIE			0x08
#define EIE_WOLIE			0x04
#define EIE_TXERIE			0x02
#define EIE_RXERIE			0x01

/*******************  Bit definition for EIR register  ************************/
#define EIR_PKTIF			0x40    /*Receive Packet Pending Interrupt Flag bit*/
#define EIR_DMAIF			0x20    /*DMA Interrupt Flag bit*/
#define EIR_LINKIF			0x10    /*Link Change Interrupt Flag bit*/
#define EIR_TXIF			0x08    /*Transmit Interrupt Flag bit*/
/*#define EIR_WOLIF			0x04    reserved rev. E*/
#define EIR_TXERIF			0x02    /*Transmit Error Interrupt Flag bit*/
#define EIR_RXERIF			0x01    /*Receive Error Interrupt Flag bit*/

// ESTAT
#define ESTAT_INT			0x80
#define ESTAT_LATECOL		0x10
#define ESTAT_RXBUSY		0x04
#define ESTAT_TXABRT		0x02
#define ESTAT_CLKRDY		0x01

/*******************  Bit definition for ECON2 register  **********************/
#define ECON2_AUTOINC		0x80    /*Automatic Buffer Pointer Increment Enable bit*/
#define ECON2_PKTDEC		0x40    /*Packet Decrement bit*/
#define ECON2_PWRSV			0x20    /*Power Save Enable bit*/
#define ECON2_VRPS			0x08    /*Voltage Regulator Power Save Enable bit*/

/*******************  Bit definition for ECON1 register  **********************/
#define ECON1_TXRST			0x80    /*Transmit Logic Reset bit*/
#define ECON1_RXRST			0x40    /*Receive Logic Reset bit*/
#define ECON1_DMAST			0x20    /*DMA Start and Busy Status bit*/
#define ECON1_CSUMEN		0x10    /*DMA Checksum Enable bit*/
#define ECON1_TXRTS			0x08    /*Transmit Request to Send bit*/
#define ECON1_RXEN			0x04    /*Receive Enable bit*/
#define ECON1_BSEL1			0x02    /*Bank Select bit 1*/
#define ECON1_BSEL0			0x01    /*Bank Select bit 0*/

// EWOLIE
#define EWOLIE_UCWOLIE		0x80
#define EWOLIE_AWOLIE		0x40
#define EWOLIE_PMWOLIE		0x10
#define EWOLIE_MPWOLIE		0x08
#define EWOLIE_HTWOLIE		0x04
#define EWOLIE_MCWOLIE		0x02
#define EWOLIE_BCWOLIE		0x01

// EWOLIR
#define EWOLIR_UCWOLIF		0x80
#define EWOLIR_AWOLIF		0x40
#define EWOLIR_PMWOLIF		0x10
#define EWOLIR_MPWOLIF		0x08
#define EWOLIR_HTWOLIF		0x04
#define EWOLIR_MCWOLIF		0x02
#define EWOLIR_BCWOLIF		0x01

// ERXFCON
#define ERXFCON_UCEN        0x80
#define ERXFCON_ANDOR       0x40
#define ERXFCON_CRCEN       0x20
#define ERXFCON_PMEN        0x10
#define ERXFCON_MPEN        0x08
#define ERXFCON_HTEN        0x04
#define ERXFCON_MCEN        0x02
#define ERXFCON_BCEN        0x01

/*******************  Bit definition for MACON1 register  *********************/
// #define MACON1_LOOPBK		0x10    /*reserved rev. E*/
#define MACON1_TXPAUS       0x08    /*Pause Control Frame Transmission Enable bit*/
#define MACON1_RXPAUS       0x04    /*Pause Control Frame Reception Enable bit*/
#define MACON1_PASSALL      0x02    /*Pass All Received Frames Enable bit*/
#define MACON1_MARXEN       0x01    /*MAC Receive Enable bit*/

/*******************  Bit definition for MACON2 register  *********************/
/* #define MACON2_MARST        0x80    reserved rev. E*/
/* #define MACON2_RNDRST       0x40    reserved rev. E*/
/* #define MACON2_MARXRST      0x08    reserved rev. E*/
/* #define MACON2_RFUNRST      0x04    reserved rev. E*/
/* #define MACON2_MATXRST      0x02    reserved rev. E*/
/* #define MACON2_TFUNRST      0x01    reserved rev. E*/

/*******************  Bit definition for MACON3 register  *********************/
#define MACON3_PADCFG2		0x80    /*Auto Pad and CRC Configuration bit 2*/
#define MACON3_PADCFG1		0x40    /*Auto Pad and CRC Configuration bit 1*/
#define MACON3_PADCFG0		0x20    /*Auto Pad and CRC Configuration bit 0*/
#define MACON3_TXCRCEN		0x10    /*Transmit CRC Enable bit*/
#define MACON3_PHDRLEN		0x08    /*Proprietary Header Enable bit*/
#define MACON3_HFRMEN		0x04    /*Huge Frame Enable bit*/
#define MACON3_FRMLNEN		0x02    /*Frame Length Checking Enable bit*/
#define MACON3_FULDPX		0x01    /*MAC Full-Duplex Enable bit*/

/*******************  Bit definition for MACON4 register  *********************/
#define MACON4_DEFER		0x40    /*Defer Transmission Enable bit (applies to half duplex only)*/
#define MACON4_BPEN			0x20    /*No Backoff During Backpressure Enable bit (applies to half duplex only)*/
#define MACON4_NOBKOFF		0x10    /*No Backoff Enable bit (applies to half duplex only)*/    
/*#define MACON4_LONGPRE		0x02    reserved rev. E*/
/*#define MACON4_PUREPRE		0x01    reserved rev. E*/

/*******************  Bit definition for MAPHSUP register  ********************/
#define MAPHSUP_RSTINTFC	0x80    /**/
#define MAPHSUP_RSTRMII		0x08    /**/

/*******************  Bit definition for MICON register  **********************/
#define MICON_RSTMII		0x80    /**/

/*******************  Bit definition for MICMD register  **********************/
#define MICMD_MIISCAN		0x02    /**/
#define MICMD_MIIRD			0x01    /**/

/*******************  Bit definition for EBSTCON register  ********************/
#define EBSTCON_PSV2		0x80    /**/
#define EBSTCON_PSV1		0x40    /**/
#define EBSTCON_PSV0		0x20    /**/
#define EBSTCON_PSEL		0x10    /**/
#define EBSTCON_TMSEL1		0x08    /**/
#define EBSTCON_TMSEL0		0x04    /**/
#define EBSTCON_TME			0x02    /**/
#define EBSTCON_BISTST		0x01    /**/

/*******************  Bit definition for MISTAT register  *********************/
#define MISTAT_NVALID		0x04    /**/
#define MISTAT_SCAN			0x02    /**/
#define MISTAT_BUSY			0x01    /**/

/*******************  Bit definition for ECOCON register  *********************/
#define ECOCON_COCON2		0x04    /**/
#define ECOCON_COCON1		0x02    /**/
#define ECOCON_COCON0		0x01    /**/

/*******************  Bit definition for EFLOCON register  ********************/
#define EFLOCON_FULDPXS		0x04    /**/
#define EFLOCON_FCEN1		0x02    /**/
#define EFLOCON_FCEN0		0x01    /**/

/*******************  Bit definition for PHCON1 register  *********************/
#define PHCON1_PRST			0x8000  /**/
#define PHCON1_PLOOPBK		0x4000  /**/
#define PHCON1_PPWRSV		0x0800  /**/
#define PHCON1_PDPXMD		0x0100  /**/

/*******************  Bit definition for PHSTAT1 register  ********************/
#define PHSTAT1_PFDPX		0x1000  /**/
#define PHSTAT1_PHDPX		0x0800  /**/
#define PHSTAT1_LLSTAT		0x0004  /**/
#define PHSTAT1_JBSTAT		0x0002  /**/

/*******************  Bit definition for PHCON2 register  *********************/
#define PHCON2_FRCLNK		0x4000  /**/
#define PHCON2_TXDIS		0x2000  /**/
#define PHCON2_JABBER		0x0400  /**/
#define PHCON2_HDLDIS		0x0100  /**/

/*******************  Bit definition for PHSTAT2 register  ********************/
#define PHSTAT2_TXSTAT		0x2000  /**/
#define PHSTAT2_RXSTAT		0x1000  /**/
#define PHSTAT2_COLSTAT		0x0800  /**/
#define PHSTAT2_LSTAT		0x0400  /**/
#define PHSTAT2_DPXSTAT		0x0200  /**/
#define PHSTAT2_PLRITY		0x0010  /**/

/*******************  Bit definition for PHIE register  ***********************/
#define PHIE_PLNKIE			0x0010  /**/
#define PHIE_PGEIE			0x0002  /**/

/*******************  Bit definition for PHIR register  ***********************/
#define PHIR_PLNKIF			0x0010  /**/
#define PHIR_PGIF			0x0004  /**/

/*******************  Bit definition for PHLCON register  *********************/
#define PHLCON_LACFG3		0x0800  /**/
#define PHLCON_LACFG2		0x0400  /**/
#define PHLCON_LACFG1		0x0200  /**/
#define PHLCON_LACFG0		0x0100  /**/
#define PHLCON_LBCFG3		0x0080  /**/
#define PHLCON_LBCFG2		0x0040  /**/
#define PHLCON_LBCFG1		0x0020  /**/
#define PHLCON_LBCFG0		0x0010  /**/
#define PHLCON_LFRQ1		0x0008  /**/
#define PHLCON_LFRQ0		0x0004  /**/
#define PHLCON_STRCH		0x0002  /**/


/**
  * @brief Initialize ENC28j60
  * @param macadr MAC addres
  * @return None
  */
void enc28j60_init(uint8_t *macadr);

// Snd/Rcv packets
/**
  * @brief 
  * @param  data 
  * @param  len 
  * @return None
  */
void enc28j60_send_packet(uint8_t *data, uint16_t len);

/**
  * @brief 
  * @param  buf 
  * @param  buflen 
  * @return uint16_t Length of received packet
  */
uint16_t enc28j60_recv_packet(uint8_t *buf, uint16_t buflen);

// R/W control registers
/**
  * @brief  Read Control Register
  * @param  adr Main register address
  * @return uint8_t Main register value	
  */
uint8_t enc28j60_rcr(uint8_t adr);

/**
  * @brief  Read register pair
  * @param  adr Main register address
  * @return uint16_t Main register value	
  */
uint16_t enc28j60_rcr16(uint8_t adr);

/**
  * @brief  Write control register
  * @param  adr Main register address
  * @param  arg Data to be written
  * @return None
  */
void enc28j60_wcr(uint8_t adr, uint8_t arg);

/**
  * @brief  Write conrol register pair
  * @param  adr Main register address
  * @param  arg Data to be written
  * @return None
  */
void enc28j60_wcr16(uint8_t adr, uint16_t arg);

/**
  * @brief  Clear bits in ETH control register (reg &= ~mask)
  * @param  adr ETH register address
  * @param  mask Bit mask
  * @return None
  */
void enc28j60_bfc(uint8_t adr, uint8_t mask);

/**
  * @brief  Set bits in control register (reg |= mask)
  * @param  adr ETH register address
  * @param  mask Bit mask
  * @return None
  */
void enc28j60_bfs(uint8_t adr, uint8_t mask);


/**
  * @brief  Clear bits in MII or MAC registers (reg &= ~mask)
  * @param  adr MAC or MII register address
  * @param  mask Bit mask
  * @return None
  */
void enc28j60_bfc_mac_mii(uint8_t adr, uint8_t mask);

/**
  * @brief  Set bits in MII or MAC registers (reg |= mask)
  * @param  adr MAC or MII register address
  * @param  mask Bit mask
  * @return None
  */
void enc28j60_bfs_mac_mii(uint8_t adr, uint8_t mask);

// R/W Rx/Tx buffer
/**
  * @brief  Read Rx/Tx buffer (at ERDPT)
  * @param  buf User buffer to be filled 
  * @param  len Buffer length
  * @return None
  */
void enc28j60_read_buffer(uint8_t *buf, uint16_t len);

/**
  * @brief  Write Rx/Tx buffer (at EWRPT)
  * @param  buf User buffer to be filled 
  * @param  len Data length
  * @return None
  */
void enc28j60_write_buffer(uint8_t *buf, uint16_t len);

// R/W PHY reg
/**
  * @brief  Read PHY register
  * @param  adr PHY address
  * @return uint16_t PHY register value
  */
uint16_t enc28j60_read_phy(uint8_t adr);

/**
  * @brief  Write PHY register
  * @param  adr  PHY address
  * @param  data Data to be written
  * @return None
  */
void enc28j60_write_phy(uint8_t adr, uint16_t data);

#endif /* ENC28J60_H */