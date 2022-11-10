#ifndef UDP_H
#define UDP_H

#pragma pack(push, 1)
typedef struct udp_packet {
    uint16_t from_port;
    uint16_t to_port;
    uint16_t len;
    uint16_t cksum;
    uint8_t data[];
} udp_packet_t;
#pragma pack(pop)

void udp_filter(eth_frame_t *frame, uint16_t len);
void udp_reply(eth_frame_t *frame, uint16_t len);
void udp_packet(eth_frame_t *frame, uint16_t len);

#endif /*UDP_H*/