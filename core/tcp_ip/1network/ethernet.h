#ifndef ETHERNET_H
#define ETHERNET_H

#include <stdint.h>
#include "lan.h"

#define ETH_TYPE_ARP	htons(0x0806) /*!< ARP payload type */
#define ETH_TYPE_IP     htons(0x0800) /*!< IP payload type */

/**
 * @brief Ethernet header.
 *
 */
#pragma pack(push, 1)
struct eth_frame {
    uint8_t to_addr[MAC_ADDR_LEN];   /*!< MAC adderess to */
    uint8_t from_addr[MAC_ADDR_LEN]; /*!< MAC address from */
    uint16_t type;                      /*!< Payload type */
    uint8_t data[];
};
#pragma pack(pop)

/**
 * @brief MAC address of host.
 *
 */
extern uint8_t mac_addr[];

/**
 * @brief Ethernet frame incapsulation of data for replying.
 * 
 * @param frame Ehternet frame.
 * @param len   Data length (Service Data Unit).
 */
void eth_reply(struct eth_frame *frame, uint16_t len);

/**
 * @brief Ethenet frame analyzer.
 * 
 * The function looks at frame type field for sending to further protocols
 * 
 * @param frame Ethernet frame pointer
 * @param len   Ethernet frame length
 */
void eth_filter(struct eth_frame *frame, uint16_t len);

/**
 * @brief Send Ethernet frame
 * 
 * @note Must be set: frame.to_addr, frame.type
 */
void eth_send(struct eth_frame *frame, uint16_t len);

#endif /* ETHERNET_H */
