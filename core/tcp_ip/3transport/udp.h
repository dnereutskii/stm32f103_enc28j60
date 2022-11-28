#ifndef UDP_H
#define UDP_H

#pragma pack(push, 1)
typedef struct udp_packet {
    uint16_t from_port; /*!< Port of the sending  process */
    uint16_t to_port;   /*!< Destination  port*/
    uint16_t len;       /*!< UDP-segment length */
    uint16_t cksum;     /*!< Checksum */
    uint8_t data[];     /*!< Service Data Unit */
} udp_packet_t;
#pragma pack(pop)

/**
 * @brief UDP-segment analyser.
 * 
 * The function 
 * 
 * @param frame Ethernet frame pointer
 * @param len   UDP-packet length
 */
void udp_filter(eth_frame_t *frame, uint16_t len);

/**
 * @brief UDP-segment incapsulation of data for replying.
 * 
 * @param frame Ethernet frame pointer
 * @param len   Data length (Service Data Unit)
 */
void udp_reply(eth_frame_t *frame, uint16_t len);

/**
 * @brief Data interchange on transport layer (OSI-4) by UDP-protocol.
 * 
 * @param frame Ethernet frame pointer 
 * @param len   Data length (Service Data Unit) 
 */
void udp_packet(eth_frame_t *frame, uint16_t len);

#endif /*UDP_H*/