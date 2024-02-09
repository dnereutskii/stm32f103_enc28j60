#include "ethernet.h"
#include "ip.h"
#include "icmp.h"

void icmp_filter(struct eth_frame *frame, uint16_t len)
{
    struct ip_packet *packet = (struct ip_packet *)frame->data;
    struct icmp_echo_packet *icmp = (struct icmp_echo_packet *)packet->data;

    if (len < sizeof(struct icmp_echo_packet))
        return;
    if (icmp->type == ICMP_TYPE_ECHO_REQUEST) {
        icmp->type = ICMP_TYPE_ECHO_REPLY;
        icmp->cksum += 8; /* Update cksum */
        ip_reply(frame, len);
    }
}

