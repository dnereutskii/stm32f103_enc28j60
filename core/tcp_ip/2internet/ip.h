#ifndef IP_H
#define IP_H

#define IP_PROTOCOL_ICMP    1
#define IP_PROTOCOL_TCP     6
#define IP_PROTOCOL_UDP     17

#pragma pack(push, 1)
typedef struct ip_packet {
    uint8_t ver_head_len;           /*!< Version (= 4) and Internet header length (= 5)*/
    uint8_t tos;                    /*!< Type of service */
    uint16_t total_len;             /*!< Total length of datagram (<= 576 octets) */
    uint16_t fragment_id;           /*!< Fragment ID */
    uint16_t flags_framgent_offset; /*!< Fragment flags and Fragment offset */
    uint8_t ttl;                    /*!< Time to live */
    uint8_t protocol;               /*!< Next level protocol */
    uint16_t cksum;                 /*!< Header checksum */
    uint32_t from_addr;             /*!< Source IP-address */
    uint32_t to_addr;               /*!< Destination IP-address */
    uint8_t data[];                 /*!< Service Data Unit */
} ip_packet_t;
#pragma pack(pop)

extern uint32_t ip_addr;    /*!< IP-address of device */

/**
 * @brief IP-packet incapsulation of data for replying.
 * 
 * @param frame Ethernet frame pointer
 * @param len   Data length (Service Data Unit)
 */
void ip_reply(eth_frame_t *frame, uint16_t len);

/**
 * @brief 
 * 
 * @param sum 
 * @param buf 
 * @param len 
 * @return uint16_t 
 */
uint16_t ip_cksum(uint32_t sum, uint8_t *buf, uint16_t len);

/**
 * @brief IP-packet analyser.
 * 
 * The function checks out ip-address and header version. Then it looks at 
 * the protocol field for further sending of the frame  to protocols 
 * on the transport layer (OSI-3)
 * 
 * @param frame Ethernet frame pointer
 * @param len   IP-packet length
 */
void ip_filter(eth_frame_t *frame, uint16_t len);

#endif /*IP_H*/
