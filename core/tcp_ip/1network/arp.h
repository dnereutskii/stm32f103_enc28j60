#ifndef ARP_H
#define ARP_H

#include <stdint.h>
#include "lan.h"
#include "ethernet.h"
/**
 * @brief 
 *
 */
#define ARP_HW_TYPE_ETH     htons(0x0001)
#define ARP_PROTO_TYPE_IP   htons(0x0800)

/**
 * @brief ARP massage types.
 *
 */
#define ARP_TYPE_REQUEST    htons(1)
#define ARP_TYPE_RESPONSE   htons(2)

/**
 * @brief ARP-message structure
 * 
 */
#pragma pack(push, 1)
struct arp_message {
    uint16_t hw_type; /*!< Data link protocol (OSI-2) -> Ethernet */
    uint16_t proto_type; /*!< Network protocol (OSI-3) -> IP */
    uint8_t hw_addr_len; /*!< MAC-address length = 6 */
    uint8_t proto_addr_len; /*!< IP-address length = 4 */
    uint16_t type; /*!< Message type: request or response*/
    uint8_t mac_addr_from[MAC_ADDR_LEN]; /*!< Source MAC-address */
    uint32_t ip_addr_from; /*!< Source IP-address */
    uint8_t mac_addr_to[MAC_ADDR_LEN]; /*!< Destination MAX-address  */
    uint32_t ip_addr_to; /*!< Destination IP-address */
};
#pragma pack(pop)

/**
 * @brief ARP-cache structure.
 *
 */
struct arp_cache_entry {
    uint32_t ip_addr;
    uint8_t mac_addr[MAC_ADDR_LEN];
};

/**
 * @brief ARP message analyzer.
 * 
 * The function checkout of datalink and protocol types, forms a response 
 * to ARP-request.
 * 
 * @param frame Ethernet frame
 * @param len   ARP-message length
 */
void arp_filter(struct eth_frame *frame, uint16_t len);

/**
 * @brief Resolves MAC address
 *
 * @param IP address for resolving.
 * @return NULL if still resolving (invalidates net_buffer if not resolved)
 * @return MAC address if resolved.
 */
uint8_t *arp_resolve(uint32_t node_ip_addr);

#endif /*ARP_H*/
