#ifndef ICMP_H
#define ICMP_H

/**
 * @brief ICMP packet type.
 *
 */
#define ICMP_TYPE_ECHO_REQUEST   (8)
#define ICMP_TYPE_ECHO_REPLY     (0)

/**
 * @brief ICMP header.
 *
 */
#pragma pack(push, 1)
struct icmp_echo_packet {
    uint8_t type;       /*!< Packet type: request or response */
    uint8_t code;       /*!< Packet code (0 - echo) */
    uint16_t cksum;     /*!< Header checksum */
    uint16_t id;        /*!< */
    uint16_t seq;       /*!< */
    uint8_t data[];     /*!< */
};
#pragma pack(pop)

/**
 * @brief ICMP-packet analyzer.
 * 
 * The function checks out type field and if echo request has been occured 
 * then it forms echo response.
 * 
 * @param frame Ehernet frame pointer.
 * @param len   ICMP-packet length.
 */
void icmp_filter(struct eth_frame *frame, uint16_t len);

#endif /* ICMP_H */
