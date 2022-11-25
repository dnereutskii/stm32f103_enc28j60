#ifndef ETHERNET_H
#define ETHERNET_H

/*
 * BE conversion
 */

#define htons(a)        ((((a) >> 8) & 0xff) | (((a) << 8) & 0xff00))
#define ntohs(a)        htons(a)

#define htonl(a)        ( (((a)>>24)&0xff) | (((a)>>8)&0xff00) |\
				        (((a)<<8)&0xff0000) | (((a)<<24)&0xff000000) )
#define ntohl(a)        htonl(a)

#define inet_addr(a,b,c,d)  ( ((uint32_t)a) | ((uint32_t)b << 8) |\
                            ((uint32_t)c << 16) | ((uint32_t)d << 24) )


#define ETH_TYPE_ARP		htons(0x0806)
#define ETH_TYPE_IP			htons(0x0800)

//#pragma pack(push, 1)
typedef struct eth_frame {
    uint8_t to_addr[6];
    uint8_t from_addr[6];
    uint16_t type;
    uint8_t data[];
} eth_frame_t;
//#pragma pack(pop)

extern uint8_t mac_addr[];

void eth_reply(eth_frame_t *frame, uint16_t len);
void eth_filter(eth_frame_t *frame, uint16_t len);

#endif /* ETHERNET_H */
