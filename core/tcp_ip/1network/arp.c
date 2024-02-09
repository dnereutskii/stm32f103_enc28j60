#include <string.h>
#include "ethernet.h"
#include "ip.h"
#include "arp.h"

static void fill_response(struct arp_message *msg); 

void arp_filter(struct eth_frame *frame, uint16_t len)
{
    struct arp_message *msg = (struct arp_message *)(frame->data);

    if(len < sizeof(arp_message_t))
        return;
    if ((msg->hw_type == ARP_HW_TYPE_ETH) &&
        (msg->proto_type == ARP_PROTO_TYPE_IP))
    {
        if ((msg->type == ARP_TYPE_REQUEST) && 
        	(msg->ip_addr_to == ip_addr))
        {
            fill_response(msg);
            eth_reply(frame, sizeof(struct arp_message));
        }         
    }
}

static void fill_response(struct arp_message *msg)
{
    msg->type = ARP_TYPE_RESPONSE;
    memcpy(msg->mac_addr_to, msg->mac_addr_from, 6);
    memcpy(msg->mac_addr_from, mac_addr, 6);
    msg->ip_addr_to = msg->ip_addr_from;
    msg->ip_addr_from = ip_addr;
}
