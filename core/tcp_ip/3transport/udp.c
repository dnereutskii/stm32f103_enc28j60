#include "stm32f1xx.h"
#include "ethernet.h"
#include "ip.h"
#include "udp.h"

void udp_filter(eth_frame_t *frame, uint16_t len)
{
    ip_packet_t *ip = (void*)(frame->data);
    udp_packet_t *udp = (void*)(ip->data);

    if(len >= sizeof(udp_packet_t))
    {
        udp_packet(frame, ntohs(udp->len) - sizeof(udp_packet_t));
    }
}

/**
 * @brief Synthesis of UDP-datagram
 * 
 * @param frame Ethernet frame pointer
 * @param len   Data length
 * @return None
 */
void udp_reply(eth_frame_t *frame, uint16_t len)
{
    ip_packet_t *ip = (void*)(frame->data);
    udp_packet_t *udp = (void*)(ip->data);
    uint16_t temp;

    len += sizeof(udp_packet_t);

    temp = udp->from_port;
    udp->from_port = udp->to_port;
    udp->to_port = temp;

    udp->len = htons(len);

    udp->cksum = 0;
    udp->cksum = ip_cksum(len + IP_PROTOCOL_UDP, (uint8_t*)udp - 8, len + 8);

    ip_reply(frame, len);
}

void udp_packet(eth_frame_t *frame, uint16_t len)
{
	ip_packet_t *ip = (void*)(frame->data);
	udp_packet_t *udp = (void*)(ip->data);
	uint8_t *data = udp->data;
	uint8_t i, count;

	for(i = 0; i < len; ++i)
    {
		// uart_write(data[i]);
    }

	// count = uart_rx_count();
    count = 10;
	if(count)
	{
		for(i = 0; i < count; ++i)
        {
			// data[i] = uart_read();
			data[i] = 'h';
        }
		udp_reply(frame, count);
	}
}