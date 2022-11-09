#include "stm32f1xx.h"
#include "ethernet.h"


uint8_t mac_addr[6] = MAC_ADDR;


void eth_reply(eth_frame_t *frame, uint16_t len)
{
	memcpy(frame->to_addr, frame->from_addr, 6);
	memcpy(frame->from_addr, mac_addr, 6);
	enc28j60_send_packet((void*)frame, len + 
		sizeof(eth_frame_t));
}


void eth_filter(eth_frame_t *frame, uint16_t len)
{
    if(len >= sizeof(eth_frame_t))
    {
        switch(frame->type)
        {
        case ETH_TYPE_ARP:
            arp_filter(frame, len - sizeof(eth_frame_t));
            break;
        case ETH_TYPE_IP:
            ip_filter(frame, len - sizeof(eth_frame_t));
            break;
        }
    }
}