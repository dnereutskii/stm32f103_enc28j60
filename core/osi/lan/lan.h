#ifndef LAN_H
#define LAN_H

/*
 * Config
 */

#define WITH_ICMP

#define MAC_ADDR            {0x00,0x13,0x37,0x01,0x23,0x45}
#define IP_ADDR	            inet_addr(192,168,0,222)

#define IP_PACKET_TTL       64


/*
 * BE conversion
 */

#define htons(a)        ((((a)>>8)&0xff)|(((a)<<8)&0xff00))
#define ntohs(a)        htons(a)

#define htonl(a)        ( (((a)>>24)&0xff) | (((a)>>8)&0xff00) |\
				        (((a)<<8)&0xff0000) | (((a)<<24)&0xff000000) )
#define ntohl(a)        htonl(a)

#define inet_addr(a,b,c,d)  ( ((uint32_t)a) | ((uint32_t)b << 8) |\
                            ((uint32_t)c << 16) | ((uint32_t)d << 24) )


void lan_init();
void lan_poll();


#endif /*LAN_H*/