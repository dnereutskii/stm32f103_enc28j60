#ifndef ETHERNET_H
#define ETHERNET_H

#define ETH_TYPE_ARP		htons(0x0806)
#define ETH_TYPE_IP			htons(0x0800)

typedef struct eth_frame {
    uint8_t to_addr[6];
    uint8_t from_addr[6];
    uint16_t type;
    uint8_t data[];
} eth_frame_t;

extern uint8_t mac_addr[];

void eth_reply(eth_frame_t *frame, uint16_t len);
void eth_filter(eth_frame_t *frame, uint16_t len);

#endif /* ETHERNET_H */