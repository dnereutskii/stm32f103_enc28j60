#ifndef ICMP_H
#define ICMP_H

#define ICMP_TYPE_ECHO_RQ   8
#define ICMP_TYPE_ECHO_RPLY 0

#pragma pack(push, 1)
typedef struct icmp_echo_packet {
    uint8_t type;
    uint8_t code;
    uint16_t cksum;
    uint16_t id;
    uint16_t seq;
    uint8_t data[];
} icmp_echo_packet_t;
#pragma pack(pop)

void icmp_filter(eth_frame_t *frame, uint16_t len);

#endif /*ICMP_H*/