#ifndef LAN_H
#define LAN_H

/*
 * Big endian conversions
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
#define htonl(a)        ((((a)>>24)&0xff) | (((a)>>8)&0xff00) |\
				        (((a)<<8)&0xff0000) | (((a)<<24)&0xff000000))

/**
 * @brief The function converts the unsigned integer netlong from network 
 * byte order (big-endian order) to host byte order. 
 */
#define ntohl(a)        htonl(a)

/**
 * @brief Converts IP address to network byte order.
 */
#define inet_addr(a,b,c,d)  (((uint32_t)a) | ((uint32_t)b << 8) |\
                            ((uint32_t)c << 16) | ((uint32_t)d << 24))

/**
 * @brief TCP/IP configurations.
 */
#define WITH_ICMP
#define MAC_ADDR            {0x00,0x80,0xE1,0x00,0x00,0x00}
#define MAC_ADDR_LEN        (6)
#define ARP_CACHE_SIZE		(3)
#define IP_ADDR	            inet_addr(192, 168, 0, 222)
#define IP_PACKET_TTL       (64)
#define IP_SUBNET_MASK      inet_addr(255, 255, 255, 0)
#define IP_DEFAULT_GATEWAY  inet_addr(192, 168, 0, 222)

extern uint8_t net_buf[];

void lan_init();
void lan_poll();


#endif /* LAN_H */

