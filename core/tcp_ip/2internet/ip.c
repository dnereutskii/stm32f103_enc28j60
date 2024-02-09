#include "ip.h"
#include "icmp.h"
#include "udp.h"
#include "lan.h"

uint32_t ip_addr = IP_ADDR;

static void fill_header(struct ip_packet *packet, uint16_t len);

uint16_t ip_cksum(uint32_t sum, uint8_t *buf, uint16_t len)
{
	while (len >= 2)
	{
		sum += ((uint16_t)*buf << 8) | *(buf+1);
		buf += 2;
		len -= 2;
	}

	if (len)
		sum += (uint16_t)*buf << 8;

	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	return ~htons((uint16_t)sum);
}

void ip_reply(struct eth_frame *frame, uint16_t len)
{
	struct ip_packet *packet = (struct ip_packet *)(frame->data);
    
    fill_header(packet, len);
    
	eth_reply(frame, len + sizeof(struct ip_packet));
}

void ip_filter(struct eth_frame *frame, uint16_t len)
{
    struct ip_packet *packet = (struct ip_packet*)(frame->data);
        
    if (len < sizeof(struct ip_packet))
        return;

    if( (packet->ver_head_len == 0x45) &&
        (packet->to_addr == ip_addr) )
    {
        len = ntohs(packet->total_len) - sizeof(struct ip_packet); /* date len */

        switch(packet->protocol)
        {
#ifdef WITH_ICMP
            case IP_PROTOCOL_ICMP:
                icmp_filter(frame, len);
                break;
#endif
            case IP_PROTOCOL_UDP:
                udp_filter(frame, len);
                break;
        }
    }
}

static void fill_header(struct ip_packet *packet, uint16_t len)
{
  	packet->total_len = htons(len + sizeof(struct ip_packet));
	packet->fragment_id = 0;
	packet->flags_framgent_offset = 0;
	packet->ttl = IP_PACKET_TTL;
	packet->cksum = 0;
	packet->to_addr = packet->from_addr;
	packet->from_addr = ip_addr;
	packet->cksum = ip_cksum(0, (uint8_t *)packet, sizeof(struct ip_packet));
}

