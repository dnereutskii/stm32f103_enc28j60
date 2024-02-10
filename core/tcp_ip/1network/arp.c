#include <string.h>
#include "ethernet.h"
#include "lan.h"
#include "ip.h"
#include "arp.h"

static void arp_fill_response(struct arp_message *msg);
static void arp_fill_request(struct arp_message *msg, uint32_t node_ip_addr);
static uint8_t *arp_search_cache(uint32_t node_ip_addr);


static struct arp_cache_entry arp_cache[ARP_CACHE_SIZE];
static uint8_t arp_cache_wr;


void arp_filter(struct eth_frame *frame, uint16_t len)
{
    struct arp_message *msg = (struct arp_message *)(frame->data);

    if(len < sizeof(struct arp_message))
        return;
    if ((msg->hw_type == ARP_HW_TYPE_ETH) &&
        (msg->proto_type == ARP_PROTO_TYPE_IP) &&
        (msg->ip_addr_to == ip_addr)) {

        switch (msg->type) {
        case ARP_TYPE_REQUEST:
            arp_fill_response(msg);
            eth_reply(frame, sizeof(struct arp_message));
            break;
        case ARP_TYPE_RESPONSE:
            if(NULL == arp_search_cache(msg->ip_addr_from)) {
                arp_cache[arp_cache_wr].ip_addr = msg->ip_addr_from;
                memcpy(arp_cache[arp_cache_wr].mac_addr, msg->mac_addr_from,
                       MAC_ADDR_LEN);
                arp_cache_wr++;
                if(arp_cache_wr == ARP_CACHE_SIZE)
                    arp_cache_wr = 0;
            }
            break;
        }
    }
}

uint8_t *arp_resolve(uint32_t node_ip_addr)
{
    struct eth_frame *frame = (struct eth_frame *)net_buf;
    struct arp_message *msg = (struct arp_message *)(frame->data);
    uint8_t *mac;
    
    /* search arp cache */
    mac = arp_search_cache(node_ip_addr);
    if(mac != NULL)
        return mac;
    
    /* send request */
    memset(frame->to_addr, 0xff, 6);
    frame->type = ETH_TYPE_ARP;
    
    arp_fill_request(msg, node_ip_addr);
    
    eth_send(frame, sizeof(struct arp_message));
    
    return NULL;
}

static void arp_fill_response(struct arp_message *msg)
{
    msg->type = ARP_TYPE_RESPONSE;
    memcpy(msg->mac_addr_to, msg->mac_addr_from, 6);
    memcpy(msg->mac_addr_from, mac_addr, 6);
    msg->ip_addr_to = msg->ip_addr_from;
    msg->ip_addr_from = ip_addr;
}

// search ARP cache
static uint8_t *arp_search_cache(uint32_t node_ip_addr)
{
    for(uint8_t i = 0; i < ARP_CACHE_SIZE; ++i) {
        if(arp_cache[i].ip_addr == node_ip_addr)
            return arp_cache[i].mac_addr;
    }
    return NULL;
}

static void arp_fill_request(struct arp_message *msg, uint32_t node_ip_addr)
{
    msg->hw_type = ARP_HW_TYPE_ETH;
    msg->proto_type = ARP_PROTO_TYPE_IP;
    msg->hw_addr_len = MAC_ADDR_LEN;
    msg->proto_addr_len = 4;
    msg->type = ARP_TYPE_REQUEST;
    memcpy(msg->mac_addr_from, mac_addr, MAC_ADDR_LEN);
    msg->ip_addr_from = ip_addr;
    memset(msg->mac_addr_to, 0x00, MAC_ADDR_LEN);
    msg->ip_addr_to = node_ip_addr;
}



