#ifndef ETHERNET_H
#define ETHERNET_H

/*
 * BE conversion
 */

/**
 * @brief The function converts the unsigned short integer hostshort from
 * host byte order to network byte order (big-endian order).
 */
#define htons(a)        ((((a) >> 8) & 0xff) | (((a) << 8) & 0xff00))

/**
 * @brief The function converts the unsigned short integer netshort from
 * network byte order (big-endian order) to host byte order.
 */
#define ntohs(a)        htons(a)

/**
 * @brief The function converts the unsigned integer hostlong from
 * host byte order to network byte order (big-endian order). 
 */
#define htonl(a)        ( (((a)>>24)&0xff) | (((a)>>8)&0xff00) |\
				        (((a)<<8)&0xff0000) | (((a)<<24)&0xff000000) )

/**
 * @brief The function converts the unsigned integer netlong from network 
 * byte order (big-endian order) to host byte order. 
 */
#define ntohl(a)        htonl(a)

/**
 * @brief
 */
#define inet_addr(a,b,c,d)  ( ((uint32_t)a) | ((uint32_t)b << 8) |\
                            ((uint32_t)c << 16) | ((uint32_t)d << 24) )


#define ETH_TYPE_ARP		htons(0x0806)
#define ETH_TYPE_IP			htons(0x0800)

#pragma pack(push, 1)
typedef struct eth_frame {
    uint8_t to_addr[6];
    uint8_t from_addr[6];
    uint16_t type;          /*!< Payload type */
    uint8_t data[];
} eth_frame_t;
#pragma pack(pop)

extern uint8_t mac_addr[];

/**
 * @brief Ethernet frame incapsulation of data for replying
 * 
 * @param frame Ehternet frame
 * @param len   Data length (Service Data Unit)
 */
void eth_reply(eth_frame_t *frame, uint16_t len);

/**
 * @brief Ethenet frame analyse.
 * 
 * The function looks at frame type field for sending to further protocols
 * 
 * @param frame Ethernet frame pointer
 * @param len   Ethernet frame length
 */
void eth_filter(eth_frame_t *frame, uint16_t len);

#endif /* ETHERNET_H */
