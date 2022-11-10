#include <string.h>
#include "stm32f1xx.h"
#include "ethernet.h"
#include "ip.h"
#include "arp.h"

void arp_filter(eth_frame_t *frame, uint16_t len)
{
    arp_message_t *msg = (void*)(frame->data);

    if(len >= sizeof(arp_message_t))
    {
        if ((msg->hw_type == ARP_HW_TYPE_ETH) &&
            (msg->proto_type == ARP_PROTO_TYPE_IP))
        {
            if ((msg->type == ARP_TYPE_REQUEST) && 
            	(msg->ip_addr_to == ip_addr))
            {
                msg->type = ARP_TYPE_RESPONSE;
                memcpy(msg->mac_addr_to, msg->mac_addr_from, 6);
                memcpy(msg->mac_addr_from, mac_addr, 6);
                msg->ip_addr_to = msg->ip_addr_from;
                msg->ip_addr_from = ip_addr;

                eth_reply(frame, sizeof(arp_message_t));
            }         
        }
    }
}
