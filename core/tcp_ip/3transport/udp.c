#include "ip.h"
#include "udp.h"
#include "buart.h"

void udp_filter(struct eth_frame *frame, uint16_t len)
{
    struct ip_packet *ip = (struct ip_packet *)(frame->data);
    struct udp_packet *udp = (struct udp_packet *)(ip->data);

    if (len < sizeof(struct udp_packet))
        return;

    udp_packet(frame, ntohs(udp->len) - sizeof(struct udp_packet));
}

void udp_reply(struct eth_frame *frame, uint16_t len)
{
    struct ip_packet *ip = (struct ip_packet *)(frame->data);
    struct udp_packet *udp = (struct udp_packet *)(ip->data);

    len += sizeof(struct udp_packet);

    uint16_t temp = udp->from_port;
    udp->from_port = udp->to_port;
    udp->to_port = temp;

    udp->len = htons(len);

    udp->cksum = 0;
    udp->cksum = ip_cksum(len + IP_PROTOCOL_UDP, (uint8_t*)udp - 8, len + 8);

    ip_reply(frame, len);
}

void udp_packet(struct eth_frame *frame, uint16_t len)
{
    struct ip_packet *ip = (struct ip_packet *)(frame->data);
    struct udp_packet *udp = (struct udp_packet *)(ip->data);
    uint8_t *data = udp->data;
    uint8_t count;

    for (uint16_t i = 0; i < len; ++i)
        uart_write_byte(data[i]);
    
    uart_write_byte('\r');

    count = uart_rx_count();
    if (count != 0) {
        for (uint16_t i = 0; i < count; ++i)
        	data[i] = uart_read();
        udp_reply(frame, count);
	}
}

uint8_t udp_send(struct eth_frame *frame, uint16_t len)
{
	struct ip_packet *ip = (struct ip_packet *)(frame->data);
	struct udp_packet *udp = (struct udp_packet *)(ip->data);

	len += sizeof(struct udp_packet);

	ip->protocol = IP_PROTOCOL_UDP;
	ip->from_addr = ip_addr;

	udp->len = htons(len);
    udp->cksum = 0;
	udp->cksum = ip_cksum(len + IP_PROTOCOL_UDP, (uint8_t*)udp-8, len+8);

    return ip_send(frame, len);
}

