#include "stm32f1xx.h"
#include "ethernet.h"
#include "ip.h"
#include "icmp.h"


void icmp_filter(eth_frame_t *frame, uint16_t len)
{
    ip_packet_t *packet = (ip_packet_t*)frame->data;
    icmp_echo_packet_t *icmp = (icmp_echo_packet_t*)packet->data;

    if(len >= sizeof(icmp_echo_packet_t) )
    {
        if(icmp->type == ICMP_TYPE_ECHO_RQ)
        {
            icmp->type = ICMP_TYPE_ECHO_RPLY;
            icmp->cksum += 8; /* Update cksum */
            ip_reply(frame, len);
        }
    }
}