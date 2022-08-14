#ifndef IP_H
#define IP_H

#define IP_PROTOCOL_ICMP    1
#define IP_PROTOCOL_TCP     6
#define IP_PROTOCOL_UDP     17

typedef struct ip_packet {
    uint8_t ver_head_len;
    uint8_t tos;
    uint16_t total_len;
    uint16_t fragment_id;
    uint16_t flags_framgent_offset;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t cksum;
    uint32_t from_addr;
    uint32_t to_addr;
    uint8_t data[];
} ip_packet_t;

void ip_reply(eth_frame_t *frame, uint16_t len);
uint16_t ip_cksum(uint32_t sum, uint8_t *buf, uint16_t len);
void ip_filter(eth_frame_t *frame, uint16_t len);

#endif /*IP_H*/