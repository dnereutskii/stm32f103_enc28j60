#ifndef ARP_H
#define ARP_H

#define ARP_HW_TYPE_ETH     htons(0x0001)
#define ARP_PROTO_TYPE_IP   htons(0x0800)

#define ARP_TYPE_REQUEST    htons(1)
#define ARP_TYPE_RESPONSE   htons(2)

#pragma pack(push, 1)
typedef struct arp_message {
    uint16_t hw_type;
    uint16_t proto_type;
    uint8_t hw_addr_len;
    uint8_t proto_addr_len;
    uint16_t type;
    uint8_t mac_addr_from[6];
    uint32_t ip_addr_from;
    uint8_t mac_addr_to[6];
    uint32_t ip_addr_to;
} arp_message_t;
#pragma pack(pop)

void arp_filter(eth_frame_t *frame, uint16_t len);

#endif /*ARP_H*/