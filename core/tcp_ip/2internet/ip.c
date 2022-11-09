#include "stm32f1xx.h" 
#include "ip.h"


uint32_t ip_addr = IP_ADDR;


uint16_t ip_cksum(uint32_t sum, uint8_t *buf, size_t len)
{
	while(len >= 2)
	{
		sum += ((uint16_t)*buf << 8) | *(buf+1);
		buf += 2;
		len -= 2;
	}

	if(len)
		sum += (uint16_t)*buf << 8;

	while(sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	return ~htons((uint16_t)sum);
}


void ip_reply(eth_frame_t *frame, uint16_t len)
{
	ip_packet_t *packet = (void*)(frame->data);

	packet->total_len = htons(len + sizeof(ip_packet_t));
	packet->fragment_id = 0;
	packet->flags_framgent_offset = 0;
	packet->ttl = IP_PACKET_TTL;
	packet->cksum = 0;
	packet->to_addr = packet->from_addr;
	packet->from_addr = ip_addr;
	packet->cksum = ip_cksum(0, (void*)packet, sizeof(ip_packet_t));

	eth_reply((void*)frame, len + sizeof(ip_packet_t));
}


void ip_filter(eth_frame_t *frame, uint16_t len)
{
    ip_packet_t *packet = (void*)(frame->data);
        
    //if(len >= sizeof(ip_packet_t))
    //{
        if( (packet->ver_head_len == 0x45) &&
            (packet->to_addr == ip_addr) )
        {
            len = ntohs(packet->total_len) - 
                sizeof(ip_packet_t);

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
    //}
}