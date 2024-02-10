#include <string.h>
#include "ethernet.h"
#include "ip.h"
#include "arp.h"
#include "enc28j60.h"

uint8_t mac_addr[] = MAC_ADDR;

void eth_reply(struct eth_frame *frame, uint16_t len)
{
	memcpy(frame->to_addr, frame->from_addr, 6);
	memcpy(frame->from_addr, mac_addr, 6);
	enc28j60_send_packet((uint8_t *)frame, len + sizeof(struct eth_frame));
}

void eth_send(struct eth_frame *frame, uint16_t len)
{
	memcpy(frame->from_addr, mac_addr, MAC_ADDR_LEN);
	enc28j60_send_packet((uint8_t *)frame, len + sizeof(struct eth_frame));
}


void eth_filter(struct eth_frame *frame, uint16_t len)
{
    if (len < sizeof(struct eth_frame))
        return;
    switch(frame->type)
    {
        case ETH_TYPE_ARP:
            arp_filter(frame, len - sizeof(struct eth_frame));
            break;
        case ETH_TYPE_IP:
            ip_filter(frame, len - sizeof(struct eth_frame));
            break;
    }
}

