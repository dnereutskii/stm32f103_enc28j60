#ifndef ICMP_H
#define ICMP_H

#define ICMP_TYPE_ECHO_RQ   8
#define ICMP_TYPE_ECHO_RPLY 0

#pragma pack(push, 1)
typedef struct icmp_echo_packet {
    uint8_t type;       /*!< Packet type: request or response */
    uint8_t code;       /*!< Packet code (0 - echo) */
    uint16_t cksum;     /*!< Header checksum */
    uint16_t id;        /*!< */
    uint16_t seq;       /*!< */
    uint8_t data[];     /*!< */
} icmp_echo_packet_t;
#pragma pack(pop)

/**
 * @brief ICMP-packet analyser.
 * 
 * The function checks out type field and if echo request has been occured 
 * then it forms echo response/ 
 * 
 * @param frame Ehernet frame pointer
 * @param len   ICMP-packet length
 */
void icmp_filter(eth_frame_t *frame, uint16_t len);

#endif /*ICMP_H*/